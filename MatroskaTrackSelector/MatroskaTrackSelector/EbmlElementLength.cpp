#include "EbmlElementLength.h"

EbmlElementLength::EbmlElementLength(uint64_t value) :
    m_value(value),
    m_minimal_encoded_size(EbmlVintUtils::get_minimal_encoded_size(value, false))
{}

inline EbmlElementLength::EbmlElementLength(std::istream& stream) :
    m_value(EbmlVintUtils::extract_from_stream(stream, false)),
    m_minimal_encoded_size(EbmlVintUtils::get_minimal_encoded_size(m_value, false))
{}

void EbmlElementLength::write(std::ostream& stream, size_t encoded_length)
{
    if (0 == encoded_length)
    {
        encoded_length = m_minimal_encoded_size;
    }
    else if (encoded_length < m_minimal_encoded_size)
    {
        throw std::length_error("The given length is too small");
    }
    else if (encoded_length > sizeof(uint64_t))
    {
        throw std::length_error("The given length is too big");
    }

    // Add marker to value
    uint64_t encoded_value = m_value;
    encoded_value |= ((uint64_t)1 << (7 * encoded_length));

    EbmlVintUtils::encode_and_write(encoded_value, encoded_length, stream);
}

std::ostream& operator<<(std::ostream& stream, EbmlElementLength ebml_vint)
{
    ebml_vint.write(stream);
    return stream;
}