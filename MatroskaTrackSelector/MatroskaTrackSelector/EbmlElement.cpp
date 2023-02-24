/*   
 *   Matroska track setter  Copyright (C) 2022  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "EbmlElement.h"

EbmlElementPtr EbmlElement::s_construct_from_stream(std::iostream& stream)
{
    EbmlElementPtr element = s_get(stream);

    // If the current element is the root, verify some properties and then overwrite it with the underlying 'Segment' element
    if (EBML_ID == element->get_id())
    {
        DEBUG_PRINT_LINE("Encountered an 'EBML' element, verifying...");
        element->_initialize_as_root();
    }
        

    return element;
}

/******************************************************************************************************/
/*************************************** Functions for iteration **************************************/
/******************************************************************************************************/
EbmlElementPtr EbmlElement::get_next_element()
{
    if (this->is_last())
        return nullptr;
    
    _seek_to(EbmlOffset::End);

    // TODO: make a new function like "advance_to_next_element" and use it explicitly instead of this ugly "optimization"
    if (1 == m_self.get_refcount())
    {
        // This is an optimization: if the refcount of the current object is 1, this function will OVERWRITE
        // the current element with the next one instead of allocating new space for the next element
        // and deallocating the space of the current element once it goes out of scope.
        m_offset = m_stream.tellg();
        m_id = EbmlElementID(m_stream);
        m_length = EbmlElementLength(m_stream);
        return m_self;
    }
    else
    {
        return _s_construct_from_parent(m_parent);
    }
}

EbmlElementPtr EbmlElement::get_first_child()
{
    _seek_to(EbmlOffset::Data);
    return _s_construct_from_parent(m_self);
}

void EbmlElement::get_unique_children(unordered_map<EbmlElementIDType, EbmlElementPtr>& children)
{
    const size_t number_of_children_to_find = children.size();
    size_t children_found = 0;

    EbmlElementPtr current_element = get_first_child();

    while (true)
    {
        // Check if a child with the ID of the current element was requested
        auto requested_child = children.find(current_element->get_id());
        if (requested_child != children.end())
        {
            ++children_found;
            requested_child->second = current_element;
        }

        // Stop iterating when reached the end or if found all requested children
        if (current_element->is_last() || (children_found == number_of_children_to_find))
            break;

        current_element = current_element->get_next_element();
    }
}

EbmlElementPtr EbmlElement::find_child(const EbmlElementIDType id)
{
    EbmlElementPtr current_element = get_first_child();

    while (true)
    {
        // If the current child has the requested ID, add it to the result vector
        if (current_element->get_id() == id)
            return current_element;

        // Stop iterating when reached the end or if found all requested children
        if (current_element->is_last())
            return nullptr;

        current_element = current_element->get_next_element();
    }
}

EbmlElements EbmlElement::get_identical_children_by_id(const EbmlElementIDType id)
{
    EbmlElements result;
    EbmlElementPtr current_element = get_first_child();

    while (true)
    {
        // If the current child has the requested ID, add it to the result vector
        if (current_element->get_id() == id)
            result.push_back(current_element);

        // Stop iterating when reached the end or if found all requested children
        if (current_element->is_last())
            break;

        current_element = current_element->get_next_element();
    }

    return result;
}

/******************************************************************************************************/
/********************************************* Data getters *******************************************/
/******************************************************************************************************/
Buffer EbmlElement::get_binary_value()
{
    Buffer result(m_length);
    _read_content(result.data());
    return result;
}

uint64_t EbmlElement::get_uint_value()
{
    _seek_to(EbmlOffset::Data);
    return Utility::read_big_endian_from_stream(m_stream, m_length);
}

int64_t EbmlElement::get_int_value()
{
    return static_cast<int64_t>(get_uint_value());
}

string EbmlElement::get_string_value()
{
    string result;
    result.resize(m_length); // Reserve one extra character for null-terminator
    //result.data()[m_length.get_value()] = '\0';
    _read_content(result.data());
    return result;
}

bool EbmlElement::get_bool_value()
{
    _seek_to(EbmlOffset::Data);
    return static_cast<bool>(m_stream.get());
}

/******************************************************************************************************/
/****************************************** Element modifiers *****************************************/
/******************************************************************************************************/
void EbmlElement::update_bool_value(bool new_value)
{
    _seek_to(EbmlOffset::Data);
    m_stream.put(static_cast<uint8_t>(new_value));
}

void EbmlElement::update_uint_value(uint64_t new_value)
{
    _seek_to(EbmlOffset::Data);
    Utility::write_big_endian_to_stream(m_stream, new_value, m_length.get_value());
}

void EbmlElement::overwrite_with_bool_element(EbmlElementIDType new_element_id, bool value)
{
    EbmlElementID new_id = new_element_id;
    EbmlElementLength new_length = 1;

    const size_t new_element_size = new_id.get_encoded_size() + new_length.get_encoded_size() + new_length;
    const int32_t element_size_delta = (int32_t)(this->get_total_size() - new_element_size);

    if (element_size_delta < 0)
    {
        throw exception("Element is too small to be overridden");
    }

    m_id = new_id;
    m_length = new_length;

    // Re-write the header of the element
    _seek_to(EbmlOffset::Header);
    m_stream << m_id;

    // If there's only one byte left to fill, extend the encoded length of the m_length element by one
    m_length.write(m_stream, (1 == element_size_delta) ? 2 : 1);
    m_stream.put(static_cast<uint8_t>(value));

    // Fill the rest of the remaining space with a Void element
    if (element_size_delta > 1)
    {
        _create_void_element(element_size_delta);
    }
}

BasicSharedPtr<EbmlElement> EbmlElement::create_boolean_child(bool at_beginning, EbmlElementIDType new_element_id, bool value)
{
    assert(m_id.get_value() == Void_ID);

    static constexpr uint64_t BOOL_ELEMENT_LENGTH_AND_VALUE_SIZE = 2;
    EbmlElementID new_element_id_obj(new_element_id);
    EbmlElementLength new_element_length(1);

    size_t new_element_size = new_element_id_obj.get_encoded_size() + new_element_length.get_encoded_size() + 1; // 1 for the bool value itself
    uint64_t new_element_offset = at_beginning ? (_get_offset(EbmlOffset::Data)) : (_get_offset(EbmlOffset::End) - new_element_size);

    // Make sure that the current element is big enough to contain a child
    if (this->get_total_size() - new_element_size < 2) // 2 is the minimal size of a Void element header
        throw exception("")

    // Write the element
    _seek_to(new_element_offset);
    m_stream << new_element_id_obj << new_element_length << static_cast<uint8_t>(value);

    // Parse the element and return it
    _seek_to(new_element_offset);
    return _s_construct_from_parent(m_parent);
}

/******************************************************************************************************/
/******************************************** Miscellaneous *******************************************/
/******************************************************************************************************/
uint64_t EbmlElement::get_distance_from(EbmlElementPtr other)
{
    if (this->get_offset() < other->get_offset())
    {
        return other->get_offset() - this->_get_offset(EbmlOffset::End);
    }
    else
    {
        return this->get_offset() - other->_get_offset(EbmlOffset::End);
    }
}

int32_t EbmlElement::move_to(EbmlElementPtr new_parent, EbmlElements& elements_to_adjust)
{
    Buffer current_element(this->get_total_size());
    pair<uint64_t, uint64_t> affected_range;
    int32_t shift_amount;

    // Store the current element in a buffer
    this->_seek_to(EbmlOffset::Header);
    m_stream.read(reinterpret_cast<char*>(current_element.data()), current_element.size());

    // Calculate the ahift amount and the range
    if (new_parent->m_offset < this->m_offset)
    {
        shift_amount = this->get_total_size();
        affected_range = std::make_pair(new_parent->_get_offset(EbmlOffset::End), this->_get_offset(EbmlOffset::End));
    }
    else
    {
        shift_amount = -static_cast<int32_t>(this->get_total_size());
        affected_range = std::make_pair(this->get_offset(), new_parent->_get_offset(EbmlOffset::Data));
    }

    // A buffer that's going to store all of the content that are going to be switched with the current_element
    Buffer part_to_switch(affected_range.second - affected_range.first - this->get_total_size());

    // Perform the switch between `part_to_switch` and the current element
    if (new_parent->m_offset < this->m_offset)
    {
        /*
        Before:
        * ----------------------------------------------------------------------------------------------------------- *
        | . . . [new_parent] [...bridge...] [parent [parent_first_part] [current_element] [parent_second_part]] . . . |
        * ----------------------------------------------------------------------------------------------------------- *
        
        After:
        * ----------------------------------------------------------------------------------------------------------- *
        | . . . [new_parent [current_element]] [...bridge...] [parent [parent_first_part] [parent_second_part]] . . . |
        * ----------------------------------------------------------------------------------------------------------- *
        */
        
        // Store the part to switch
        new_parent->_seek_to(EbmlOffset::End);
        m_stream.read(reinterpret_cast<char*>(part_to_switch.data()), part_to_switch.size());

        // Write buffers in new order
        new_parent->_seek_to(EbmlOffset::End);
        m_stream.write(reinterpret_cast<char*>(current_element.data()), current_element.size());
        m_stream.write(reinterpret_cast<char*>(part_to_switch.data()), part_to_switch.size());

    // Update referencing objects:
        // Current element offset
        this->m_offset = new_parent->_get_offset(EbmlOffset::End);

        // New parent size
        _seek_to(new_parent->m_offset + new_parent->m_id.get_encoded_size());
        new_parent->m_length = new_parent->m_length + current_element.size();
        m_stream << new_parent->m_length;

        // Old parent offset
        m_parent->m_offset += current_element.size();

        // Old parent size
        _seek_to(m_parent->m_offset + m_parent->m_id.get_encoded_size());
        m_parent->m_length = m_parent->m_length - current_element.size();
        m_stream << m_parent->m_length;
    }
    else
    {
        /*
        Before:
        * ------------------------------------------------------------------------------------------------------------------------------------------------- *
        | . . . [parent [parent_first_part] [current_element] [parent_second_part]] [...bridge...] [new_parent [new_parent_header] [new_parent_data]] . . . |
        * ------------------------------------------------------------------------------------------------------------------------------------------------- *

        After:
        * ------------------------------------------------------------------------------------------------------------------------------------------------- *
        | . . . [parent [parent_first_part] [parent_second_part]] [...bridge...] [new_parent [new_parent_header] [current_element] [new_parent_data]] . . . |
        * ------------------------------------------------------------------------------------------------------------------------------------------------- *
        */

        // Store the part to switch
        this->_seek_to(EbmlOffset::End);
        m_stream.read(reinterpret_cast<char*>(part_to_switch.data()), part_to_switch.size());

        // Write buffers in new order
        this->_seek_to(EbmlOffset::Header);
        m_stream.write(reinterpret_cast<char*>(part_to_switch.data()), part_to_switch.size());
        m_stream.write(reinterpret_cast<char*>(current_element.data()), current_element.size());

    // Update referencing objects:
        // Old parent size
        _seek_to(m_parent->m_offset + m_parent->m_id.get_encoded_size());
        m_parent->m_length = m_parent->m_length - current_element.size();
        m_stream << m_parent->m_length;

        // New parent offset
        new_parent->m_offset -= current_element.size();

        // Current element offset
        this->m_offset = new_parent->_get_offset(EbmlOffset::Data);

        // New parent size
        _seek_to(new_parent->m_offset + new_parent->m_id.get_encoded_size());
        new_parent->m_length = new_parent->m_length + current_element.size();
        m_stream << new_parent->m_length;
    }

    // Update the parent of the current element
    m_parent = new_parent;

    // Adjust offset of every element that was in the affected range
    for (auto& element : elements_to_adjust)
    {
        if ((element->get_offset() > affected_range.first) && (element->get_offset() < affected_range.second))
        {
            element->m_offset += shift_amount;
        }
    }

    return shift_amount;
}

/******************************************************************************************************/
/**************************************** Internal Constructors ***************************************/
/******************************************************************************************************/
EbmlElement::EbmlElement(std::iostream& stream) :
    m_stream(stream),
    m_offset(stream.tellg()),
    m_id(stream),
    m_length(stream),
    m_parent(),
    m_self()
{}

EbmlElement::EbmlElement(EbmlElementPtr parent) :
    m_stream(parent->m_stream),
    m_offset(parent->m_stream.tellg()),
    m_id(parent->m_stream),
    m_length(parent->m_stream),
    m_parent(parent),
    m_self()
{}

/******************************************************************************************************/
/****************************************** Internal Utility ******************************************/
/******************************************************************************************************/
EbmlElementPtr EbmlElement::_s_construct_from_parent(EbmlElementPtr& parent)
{
    return s_get(parent);
}

constexpr uint64_t EbmlElement::_get_offset(const EbmlOffset seek_pos) const
{
    switch (seek_pos)
    {
    case EbmlOffset::Header:
        return m_offset;

    case EbmlOffset::Data:
        return m_offset + m_id.get_encoded_size() + m_length.get_encoded_size();

    case EbmlOffset::End:
        return m_offset + m_id.get_encoded_size() + m_length.get_encoded_size() + m_length;

    default:
        throw exception("Unexpected value");
    }
}

void EbmlElement::_read_content(void* container) const
{
    _seek_to(EbmlOffset::Data);
    m_stream.read(reinterpret_cast<char*>(container), m_length);
}

void EbmlElement::_initialize_as_root()
{
    unordered_map<EbmlElementIDType, EbmlElementPtr> children{
        {DocType_ID, nullptr},
        {EBMLMaxIDLength_ID, nullptr},
        {EBMLMaxSizeLength_ID, nullptr}
    };

    get_unique_children(children);

    // Check that we are deling with a mtroska document
    if ((children[DocType_ID].is_null()) ||
        (children[DocType_ID]->get_string_value() != "matroska"))
    {
        throw InvalidMatroskaFile();
    }

    // Check that the maximum ID length of the current stream is supported
    if ((!children[EBMLMaxIDLength_ID].is_null()) &&
        (children[EBMLMaxIDLength_ID]->get_uint_value() > sizeof(EbmlElementIDType)))
    {
        throw UnsupportedMatroskaFile();
    }

    // Check that the maximum element size length of the current stream is supported
    if ((!children[EBMLMaxSizeLength_ID].is_null()) &&
        (children[EBMLMaxSizeLength_ID]->get_uint_value() > sizeof(EbmlElementLengthType)))
    {
        throw UnsupportedMatroskaFile();
    }

    // Set the current element to be the 'Segment' element
    _seek_to(EbmlOffset::End);
    m_offset = m_stream.tellg();
    m_id = EbmlElementID(m_stream);
    m_length = EbmlElementLength(m_stream);

    // Make sure that it's indeed the 'Segment' element
    if (Segment_ID != m_id)
        throw InvalidMatroskaFile();

    DEBUG_PRINT_LINE("The 'EBML' element has been verified and now points to the corresponding 'Segment' element");
}

void EbmlElement::_create_void_element(size_t size)
{
    assert(size >= 2);

    EbmlElementID void_element_id = Void_ID;

    // The size of the data is AT MOST "size-2" because the minimum length of the size is 1 byte and the size of the ID is always 1
    EbmlElementLength void_length = size - 2;

    // If the total size of the element is bigger than the required size, keep decreasing the size until it's not bigger
    while ((void_element_id.get_encoded_size() + void_length.get_minimal_encoded_size() + void_length.get_value()) > size)
    {
        void_length = void_length.get_value() - 1;
    }

    // There are rare cases when the total element size is one byte smaller than the required size
    // this happens when the reqired size is one of the following values: [2**7+2, 2**14+3, 2**21+4, ...]
    // In order to handle this case, we expand the encoded length of the element size by one byte.
    size_t encoded_length_size = void_length.get_minimal_encoded_size();
    if ((void_element_id.get_encoded_size() + void_length.get_minimal_encoded_size() + void_length.get_value()) == size - 1)
        ++encoded_length_size;

    // Write the header of the void element
    m_stream << void_element_id;
    void_length.write(m_stream, encoded_length_size);
}

std::ostream& operator<<(std::ostream& stream, const EbmlElementPtr& element)
{
    stream << std::hex << 
              "Offset: 0x"  << element->get_offset() <<
              "; ID: 0x"     << element->get_id() <<
              "; Length: 0x" << element->get_total_size() << std::dec;

    return stream;
}
