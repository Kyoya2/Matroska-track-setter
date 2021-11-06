#include "EbmlElement.h"

template<const EbmlElementSpecifications& element_specificaion>
inline void EbmlElement<element_specificaion>::_seek_to(const EbmlSeekPosition seek_pos) const
{
    switch (seek_pos)
    {
    case EbmlSeekPosition::Header:
        m_stream.seekp(m_offset);
        return;

    case EbmlSeekPosition::Data:
        m_stream.seekp(m_offset + m_id.get_encoded_size() + m_length.get_encoded_size());
        return;

    case EbmlSeekPosition::End:
        m_stream.seekp(m_offset + m_id.get_encoded_size() + m_length.get_encoded_size() + m_length.get_value());
        return;

    default:
        throw std::runtime_error("Unimplemented");
    }
}
