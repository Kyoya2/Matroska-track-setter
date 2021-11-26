#include "EbmlElementLength.h"

EbmlElementLength::EbmlElementLength(EbmlElementLengthType value) :
    m_encoded_size(EbmlVintUtils::get_minimal_encoded_size(value, false)),
    m_value(value),
    m_minimal_encoded_size(m_encoded_size)
{}

EbmlElementLength::EbmlElementLength(std::istream& stream) :
    m_encoded_size(0),
    m_value(EbmlVintUtils::extract_from_stream<EbmlElementLengthType>(stream, false, &m_encoded_size)),
    m_minimal_encoded_size(EbmlVintUtils::get_minimal_encoded_size(m_value, false))
{}

void EbmlElementLength::write(std::ostream& stream, size_t encoded_length) const
{
    if (0 == encoded_length)
    {
        encoded_length = m_encoded_size;
    }
    else if (encoded_length < m_minimal_encoded_size)
    {
        throw VINTEncodingError("The given length is too small");
    }
    else if (encoded_length > sizeof(EbmlElementLengthType))
    {
        throw VINTEncodingError("The given length is too big");
    }

    // Add marker to value
    EbmlElementLengthType encoded_value = m_value;
    encoded_value |= ((EbmlElementLengthType)1 << (7 * encoded_length));

    EbmlVintUtils::encode_and_write(encoded_value, encoded_length, stream);

    // Update encoded size to match
    m_encoded_size = encoded_length;
}

std::ostream& operator<<(std::ostream& stream, const EbmlElementLength& element_length)
{
    element_length.write(stream);
    return stream;
}

std::istream& operator>>(std::istream& stream, EbmlElementLength& element_length)
{
    element_length = EbmlElementLength(stream);
    return stream;
}