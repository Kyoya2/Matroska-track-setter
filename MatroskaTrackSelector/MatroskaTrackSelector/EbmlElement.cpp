/*
 * Copyright 2021 Kyoya2
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "EbmlElement.h"

BasicSharedPtr<EbmlElement> EbmlElement::s_construct_from_stream(std::iostream& stream)
{
    BasicSharedPtr<EbmlElement> element = s_get(stream);

    // If the current element is the root, verify some properties and then overwrite it with the underlying 'Segment' element
    if (EBML_ID == element->get_id().get_value())
    {
        DEBUG_PRINT_LINE("Encountered an 'EBML' element, verifying...");
        element->_initialize_as_root();
    }
        

    return element;
}

/******************************************************************************************************/
/*************************************** Functions for iteration **************************************/
/******************************************************************************************************/
BasicSharedPtr<EbmlElement> EbmlElement::get_next_element()
{
    if (this->is_last())
        throw NoMoreElements();
    
    _seek_to(EbmlOffset::End);

    if (1 == m_self.get_refcount())
    {
        // This is an optimization: if the refcount of the current object is 1, this function will OVERWRITE
        // the current element with the next one instead of allocating new space for the next element
        // and deallocating the space of the current element once it goes out of scope.
        m_offset = m_stream.get().tellg();
        m_id = EbmlElementID(m_stream.get());
        m_length = EbmlElementLength(m_stream.get());
        return m_self;
    }
    else
    {
        return _s_construct_from_parent(m_parent);
    }
}

BasicSharedPtr<EbmlElement> EbmlElement::get_first_child()
{
    _seek_to(EbmlOffset::Data);
    return _s_construct_from_parent(m_self);
}

void EbmlElement::get_unique_children(unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>>& children)
{
    const size_t number_of_children_to_find = children.size();
    size_t children_found = 0;

    BasicSharedPtr<EbmlElement> current_element = get_first_child();

    while (true)
    {
        // Check if a child with the ID of the current element was requested
        auto requested_child = children.find(current_element->get_id().get_value());
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

BasicSharedPtr<EbmlElement> EbmlElement::find_child(const EbmlElementIDType id)
{
    BasicSharedPtr<EbmlElement> current_element = get_first_child();

    while (true)
    {
        // If the current child has the requested ID, add it to the result vector
        if (current_element->get_id().get_value() == id)
            return current_element;

        // Stop iterating when reached the end or if found all requested children
        if (current_element->is_last())
            return nullptr;

        current_element = current_element->get_next_element();
    }
}

vector<BasicSharedPtr<EbmlElement>> EbmlElement::get_identical_children_by_id(const EbmlElementIDType id)
{
    vector<BasicSharedPtr<EbmlElement>> result;
    BasicSharedPtr<EbmlElement> current_element = get_first_child();

    while (true)
    {
        // If the current child has the requested ID, add it to the result vector
        if (current_element->get_id().get_value() == id)
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
Buffer EbmlElement::get_binary_value() const
{
    Buffer result(m_length.get_value());
    _read_content(result.data());
    return result;
}

uint64_t EbmlElement::get_uint_value() const
{
    _seek_to(EbmlOffset::Data);
    return Utility::read_big_endian_from_stream(m_stream, m_length.get_value());
}

int64_t EbmlElement::get_int_value() const
{
    return static_cast<int64_t>(get_uint_value());
}

string EbmlElement::get_string_value() const
{
    string result;
    result.resize(m_length.get_value()); // Reserve one extra character for null-terminator
    //result.data()[m_length.get_value()] = '\0';
    _read_content(result.data());
    return result;
}

bool EbmlElement::get_bool_value() const
{
    _seek_to(EbmlOffset::Data);
    return static_cast<bool>(m_stream.get().get());
}

/******************************************************************************************************/
/****************************************** Element modifiers *****************************************/
/******************************************************************************************************/
void EbmlElement::change_bool_value(bool new_value)
{
    _seek_to(EbmlOffset::Data);
    m_stream.get().put(static_cast<uint8_t>(new_value));
}

void EbmlElement::overwrite_with_bool_element(EbmlElementIDType new_element_id, bool value)
{
    EbmlElementID new_id = new_element_id;
    EbmlElementLength new_length = 1;

    const size_t new_element_size = new_id.get_encoded_size() + new_length.get_encoded_size() + new_length.get_value();
    const int32_t element_size_delta = (int32_t)(this->get_total_size() - new_element_size);

    if (element_size_delta < 0)
    {
        throw ElementTooSmall("The current element is too small to be overwritten with the given element");
    }

    m_id = new_id;
    m_length = new_length;

    // Re-write the header of the element
    _seek_to(EbmlOffset::Header);
    m_stream << m_id;

    // If there's only one byte left to fill, extend the encoded length of the m_length element by one
    m_length.write(m_stream, (1 == element_size_delta) ? 2 : 1);
    m_stream.get().put(static_cast<bool>(value));

    // Fill the rest of the remaining space with a Void element
    if (element_size_delta > 1)
    {
        _create_void_element(element_size_delta);
    }
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

EbmlElement::EbmlElement(BasicSharedPtr<EbmlElement> parent) :
    m_stream(parent->m_stream),
    m_offset(parent->m_stream.get().tellg()),
    m_id(parent->m_stream),
    m_length(parent->m_stream),
    m_parent(parent),
    m_self()
{}

/******************************************************************************************************/
/****************************************** Internal Utility ******************************************/
/******************************************************************************************************/
BasicSharedPtr<EbmlElement> EbmlElement::_s_construct_from_parent(BasicSharedPtr<EbmlElement>& parent)
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
        return m_offset + m_id.get_encoded_size() + m_length.get_encoded_size() + m_length.get_value();
    }
    throw UnexpectedValueException();
}

void EbmlElement::_read_content(void* container) const
{
    _seek_to(EbmlOffset::Data);
    m_stream.get().read(reinterpret_cast<char*>(container), m_length.get_value());
}

void EbmlElement::_initialize_as_root()
{
    unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>> children{
        {DocType_ID, nullptr},
        {EBMLMaxIDLength_ID, nullptr},
        {EBMLMaxSizeLength_ID, nullptr}
    };

    get_unique_children(children);

    // Check that we are deling with a mtroska document
    if ((children[DocType_ID].is_null()) ||
        (children[DocType_ID]->get_string_value() != "matroska"))
    {
        throw UnsupportedDocument("This is not a matroska document");
    }

    // Check that the maximum ID length of the current stream is supported
    if ((!children[EBMLMaxIDLength_ID].is_null()) &&
        (children[EBMLMaxIDLength_ID]->get_uint_value() > sizeof(EbmlElementIDType)))
    {
        throw UnsupportedDocument("Max ID length is bigger then the supported size");
    }

    // Check that the maximum element size length of the current stream is supported
    if ((!children[EBMLMaxSizeLength_ID].is_null()) &&
        (children[EBMLMaxSizeLength_ID]->get_uint_value() > sizeof(EbmlElementLengthType)))
    {
        throw UnsupportedDocument("Max element size length is bigger then the supported size");
    }

    // Set the current element to be the 'Segment' element
    _seek_to(EbmlOffset::End);
    m_offset = m_stream.get().tellg();
    m_id = EbmlElementID(m_stream.get());
    m_length = EbmlElementLength(m_stream.get());

    // Make sure that it's indeed the 'Segment' element
    if (Segment_ID != m_id.get_value())
        throw UnexpectedElementException("Expected segment element");

    DEBUG_PRINT_LINE("The 'EBML' element has been verified and now points to the corresponding 'Segment' element");
}

void EbmlElement::_create_void_element(size_t size)
{
    if (size < 2)
    {
        throw SizeTooSmall("Can't create a Void element of less than 2 bytes");
    }

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
    // In order to handle this case, we expand the ncoded length of the element size by one byte.
    size_t encoded_length_size = void_length.get_minimal_encoded_size();
    if ((void_element_id.get_encoded_size() + void_length.get_minimal_encoded_size() + void_length.get_value()) == size - 1)
        ++encoded_length_size;

    // Write the header of the void element
    m_stream << void_element_id;
    void_length.write(m_stream, encoded_length_size);
}

std::ostream& operator<<(std::ostream& stream, const BasicSharedPtr<EbmlElement>& element)
{
    stream << std::hex << 
              "Offset: 0x"  << element->get_offset() <<
              "; ID: 0x"     << element->get_id().get_value() <<
              "; Length: 0x" << element->get_total_size() << std::dec;

    return stream;
}
