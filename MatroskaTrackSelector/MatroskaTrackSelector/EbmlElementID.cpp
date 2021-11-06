#include "EbmlElementID.h"

EbmlElementID::EbmlElementID(uint64_t value) :
    m_value(value),
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(value, true))
{}

EbmlElementID::EbmlElementID(std::istream& stream) :
    m_value(EbmlVintUtils::extract_from_stream(stream, true)),
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(m_value, true))
{}

void EbmlElementID::write(std::ostream& stream)
{
    EbmlVintUtils::encode_and_write(m_value, m_encoded_size, stream);
}

std::ostream& operator<<(std::ostream& stream, EbmlElementID ebml_vint)
{
    ebml_vint.write(stream);
    return stream;
}