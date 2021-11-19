#include "EbmlElement.h"

BasicSharedPtr<EbmlElement> EbmlElement::s_construct_from_stream(std::iostream& stream)
{
    BasicSharedPtr<EbmlElement> element = s_get(stream);

    // If the current element is the root, verify some properties and then overwrite it with the underlying 'Segment' element
    if (GET_ID(EBML) == element->get_id().get_value())
        element->_initialize_as_root();

    return element;
}

void EbmlElement::_initialize_as_root()
{
    unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>> children{
        {GET_ID(EBMLMaxIDLength), nullptr},
        {GET_ID(EBMLMaxSizeLength), nullptr}
    };

    get_unique_children(children);

    // Check that the maximum ID length of the current stream is supported
    if ((!children[GET_ID(EBMLMaxIDLength)].is_null()) &&
        (GET_CHILD_VALUE(children, EBMLMaxIDLength) > sizeof(EbmlElementIDType)))
    {
        throw std::exception("Max ID length is bigger then the supported size");
    }
    
    // Check that the maximum element size length of the current stream is supported
    if ((!children[GET_ID(EBMLMaxSizeLength)].is_null()) &&
        (GET_CHILD_VALUE(children, EBMLMaxSizeLength) > sizeof(EbmlElementLengthType)))
    {
        throw std::exception("Max element size length is bigger then the supported size");
    }

    // Set the current element to be the 'Segment' element
    _seek_to(EbmlOffset::End);
    m_offset = m_stream.tellg();
    m_id = EbmlElementID(m_stream);
    m_length = EbmlElementLength(m_stream);

    // Make sure that it's indeed the 'Segment' element
    if (GET_ID(Segment) != m_id.get_value())
        throw std::exception("Expected segment element");
}

/******************************************************************************************************/
/*************************************** Functions for iteration **************************************/
/******************************************************************************************************/
BasicSharedPtr<EbmlElement> EbmlElement::get_next_element()
{
    if (this->is_last())
        throw std::out_of_range("No next element");
    
    _seek_to(EbmlOffset::End);
    return _s_construct_from_parent(m_parent);
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
Buffer EbmlElement::binary_value() const
{
    Buffer result(m_length.get_value());
    _read_content(result.data());
    return result;
}

uint64_t EbmlElement::uint_value() const
{
    return uint64_t();
}

int64_t EbmlElement::int_value() const
{
    return int64_t();
}

/******************************************************************************************************/
/**************************************** Internal Constructors ***************************************/
/******************************************************************************************************/
EbmlElement::EbmlElement(std::iostream& stream) :
    m_stream(stream),
    m_offset(stream.tellg()),
    m_id(stream),
    m_length(stream),
    m_parent()
{}

EbmlElement::EbmlElement(BasicSharedPtr<EbmlElement> parent) :
    m_stream(parent->m_stream),
    m_offset(parent->m_stream.tellg()),
    m_id(parent->m_stream),
    m_length(parent->m_stream),
    m_parent(parent)
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
    throw std::runtime_error("Unrecognized value");
}

inline void EbmlElement::_seek_to(const EbmlOffset seek_pos) const
{
    _seek_to(_get_offset(seek_pos));
}

inline void EbmlElement::_seek_to(uint64_t seek_pos) const
{
    m_stream.seekp(seek_pos);
}

void EbmlElement::_read_content(void* container) const
{
    _seek_to(EbmlOffset::Data);
    m_stream.read(reinterpret_cast<char*>(container), m_length.get_value());
}