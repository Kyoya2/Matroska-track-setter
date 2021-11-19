#include "EbmlElement.h"

// Public constructor
EbmlElement::EbmlElement(std::iostream& stream) :
    m_stream(stream),
    m_offset(stream.tellg()),
    m_id(stream),
    m_length(stream),
    m_parent()
{}

EbmlElement::~EbmlElement()
{}

ElementIterator EbmlElement::begin()
{
    return ElementIterator(m_self);
}

/******************************************************************************************************/
/*************************************** Functions for iteration **************************************/
/******************************************************************************************************/
BasicSharedPtr<EbmlElement> EbmlElement::get_next_element()
{
    if (this->is_last())
        throw std::out_of_range("No next element");

    _seek_to(EbmlOffset::End);
    return s_get(m_parent);
}

BasicSharedPtr<EbmlElement> EbmlElement::get_first_child()
{
    _seek_to(EbmlOffset::Data);
    return s_get(m_self);
}

void EbmlElement::find_children(unordered_map<EbmlElementIDType, BasicSharedPtr<EbmlElement>>& children)
{
    BasicSharedPtr<EbmlElement> current_element = get_first_child();

    while (true)
    {
        // Check if a child with the ID of the current element was requested
        auto requested_child = children.find(current_element->get_id().get_value());
        if (requested_child != children.end())
        {
            requested_child->second = current_element;
        }

        if (current_element->is_last())
            break;

        current_element = current_element->get_next_element();
    }
}

/******************************************************************************************************/
/********************************************* Data getters *******************************************/
/******************************************************************************************************/
template<>
Buffer EbmlElement::get_data()
{
    
}

// Private constructor
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