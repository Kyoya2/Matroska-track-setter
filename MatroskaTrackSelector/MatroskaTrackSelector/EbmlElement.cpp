#include "EbmlElement.h"

template<typename ...Args>
inline BasicSharedPtr<EbmlElement> EbmlElement::s_get(Args&& ...args)
{
    BasicSharedPtr<EbmlElement> result = BasicSharedPtr<EbmlElement>::make_shared(std::forward<Args>(args)...);
    result->m_self = result;
    result->m_self.release_ownership_unsafe();
    return result;
}

// Public constructor
EbmlElement::EbmlElement(std::iostream& stream) :
    m_stream(stream),
    m_offset(stream.tellg()),
    m_id(stream),
    m_length(stream),
    m_parent()
{
    if (GET_ID(EBML) == m_id.get_value())
    {

    }
}

/******************************************************************************************************/
/*************************************** Functions for iteration **************************************/
/******************************************************************************************************/
BasicSharedPtr<EbmlElement> EbmlElement::get_next_element()
{
    _seek_to(EbmlOffset::End);
    return s_get(m_self);
}

BasicSharedPtr<EbmlElement> EbmlElement::get_next_element(EbmlElementIDType id)
{
    return BasicSharedPtr<EbmlElement>();
}

BasicSharedPtr<EbmlElement> EbmlElement::get_first_child()
{
    return BasicSharedPtr<EbmlElement>();
}

BasicSharedPtr<EbmlElement> EbmlElement::get_child(EbmlElementIDType id)
{
    return BasicSharedPtr<EbmlElement>();
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