#include "EbmlElement.h"

EbmlElement::EbmlElement(std::iostream& stream, EbmlElement* parent) :
    m_stream(stream),
    m_offset(stream.tellg()),
    m_id(stream),
    m_length(stream),
    m_parent(parent)
{
    if (GET_ID(EBML) == m_id.get_value())
    {

    }
}

/******************************************************************************************************/
/****************************************** Internal Utility ******************************************/
/******************************************************************************************************/
constexpr uint64_t EbmlElement::_get_offset(const EbmlSeekPosition seek_pos) const
{
    switch (seek_pos)
    {
    case EbmlSeekPosition::Header:
        return m_offset;

    case EbmlSeekPosition::Data:
        return m_offset + m_id.get_encoded_size() + m_length.get_encoded_size();

    case EbmlSeekPosition::End:
        return m_offset + m_id.get_encoded_size() + m_length.get_encoded_size() + m_length.get_value();
    }
}

inline void EbmlElement::_seek_to(const EbmlSeekPosition seek_pos) const
{
    m_stream.seekp(_get_offset(seek_pos));
}
