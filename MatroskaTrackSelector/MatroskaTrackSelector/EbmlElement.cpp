#include "EbmlElement.h"

EbmlElement::EbmlElement(std::iostream& stream) :
    m_stream(stream),
    m_offset(stream.tellg()),
    m_id(stream),
    m_length(stream),
    m_parent(nullptr)
{
    if (GET_ID(EBML) == m_id.get_value())
    {

    }
}

/******************************************************************************************************/
/*************************************** Functions for iteration **************************************/
/******************************************************************************************************/
shared_ptr<EbmlElement> EbmlElement::get_next_element()
{
    _seek_to(EbmlOffset::End);
    return std::make_shared<EbmlElement>(*this);
}

shared_ptr<EbmlElement> EbmlElement::get_next_element(EbmlElementIDType id)
{
    return shared_ptr<EbmlElement>();
}

shared_ptr<EbmlElement> EbmlElement::get_first_child()
{
    return shared_ptr<EbmlElement>();
}

shared_ptr<EbmlElement> EbmlElement::get_child(EbmlElementIDType id)
{
    return shared_ptr<EbmlElement>();
}

/******************************************************************************************************/
/**************************************** Internal Constructors ***************************************/
/******************************************************************************************************/
EbmlElement::EbmlElement(shared_ptr<EbmlElement> parent) :
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

/******************************************************************************************************/
/******************************************* Iterator Stuff *******************************************/
/******************************************************************************************************/
EbmlElement::Iterator::Iterator(EbmlElement& parent) :
    m_parent(parent),
    m_current_element(nullptr)
{
    if (parent.get_length().get_value() != 0)
    {
        m_parent._seek_to(EbmlOffset::Data);
        m_current_element = std::make_shared<EbmlElement>(m_parent.m_stream);
    }
}

shared_ptr<EbmlElement> EbmlElement::Iterator::operator*()
{
    return m_current_element;
}

EbmlElement::Iterator& EbmlElement::Iterator::operator++()
{
    // Seek to end of last element and read
    m_current_element->_seek_to(EbmlOffset::End);
    m_current_element = std::make_shared<EbmlElement>(m_parent.m_stream);
    return *this;
}

bool operator!=(const EbmlElement::Iterator& current, uint64_t end_offset)
{
    return (current.m_parent.get_length().get_value() != 0) && (current.m_current_element->end() != end_offset);
}
