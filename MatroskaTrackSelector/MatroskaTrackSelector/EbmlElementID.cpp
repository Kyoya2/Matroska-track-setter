#include "EbmlElementID.h"

EbmlElementID::EbmlElementID(EbmlElementIDType value) :
    m_value(value),
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(value, true))
{}

EbmlElementID::EbmlElementID(std::istream& stream) :
    m_value(EbmlVintUtils::extract_from_stream<EbmlElementIDType>(stream, true)),
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(m_value, true))
{}

void EbmlElementID::write(std::ostream& stream) const
{
    EbmlVintUtils::encode_and_write(m_value, m_encoded_size, stream);
}

std::ostream& operator<<(std::ostream& stream, const EbmlElementID& element_id)
{
    element_id.write(stream);
    return stream;
}

std::istream& operator>>(std::istream& stream, EbmlElementID& element_id)
{
    element_id = EbmlElementID(stream);
    return stream;
}