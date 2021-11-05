#pragma once

#include <algorithm>
#include <fstream>
#include "Common.h"

template<bool value_with_vint_marker>
class EbmlVint
{
public:
    EbmlVint(uint64_t value);
    explicit EbmlVint(std::istream& stream);

    EbmlVint(const EbmlVint& other) = default;
    EbmlVint& operator=(const EbmlVint& other) = default;

public:
    inline uint64_t get_value() { return m_value; }
    void write(std::ostream& stream, size_t encoded_length = 0);

private:
    static inline uint64_t _s_remove_vint_marker(uint64_t value);
    inline size_t _s_get_minimal_encoded_size(uint64_t value);
    static uint64_t _s_extract_from_stream(std::istream& stream);

private:
    uint64_t m_value;
    size_t m_minimal_encoded_size;
};

template<bool value_with_vint_marker>
EbmlVint<value_with_vint_marker>::EbmlVint(uint64_t value) :
    m_value(value),
    m_minimal_encoded_size(_s_get_minimal_encoded_size(value))
{
    if (m_minimal_encoded_size > sizeof(uint64_t))
    {
        throw std::overflow_error("Value is too big");
    }
}

template<bool value_with_vint_marker>
inline EbmlVint<value_with_vint_marker>::EbmlVint(std::istream& stream) :
    m_value(_s_extract_from_stream(stream)),
    m_minimal_encoded_size(_s_get_minimal_encoded_size(m_value))
{}

template<bool value_with_vint_marker>
inline uint64_t EbmlVint<value_with_vint_marker>::_s_remove_vint_marker(uint64_t value)
{
    return value ^ Utility::get_msb(value);
}

template<bool value_with_vint_marker>
inline size_t EbmlVint<value_with_vint_marker>::_s_get_minimal_encoded_size(uint64_t value)
{
    // The number of bits required to represent the number
    size_t bit_count = Utility::get_msb_index(value) + 1;

    // The number of bytes required to represent the number
    size_t byte_count = (bit_count / 8) + ((bit_count % 8 == 0) ? 0 : 1);

    // If the value already has the VINT_MARKER, the byte count is the minimal size
    if (value_with_vint_marker)
    {
        return byte_count;
    }

    // Check whether the number of bits with the addition of the bits for VINT_MARKER
    // can be stored using the same byte count
    if (bit_count + byte_count  <= byte_count * 8)
        return byte_count;
    else
        return byte_count + 1;
}

template<bool value_with_vint_marker>
inline uint64_t EbmlVint<value_with_vint_marker>::_s_extract_from_stream(std::istream& stream)
{
    uint64_t result = stream.get();

    // Throw if the size is at more than 8 bytes
    if (0 == result)
    {
        throw std::length_error("The given length is too big");
    }

    // Calculate the size of the VINT by calculating length of (VINT_WIDTH + VINT_DATA)
    size_t size_of_vint = 8 - Utility::get_msb_index(result);

    // Unset VINT_MARKER
    if (!value_with_vint_marker)
        result ^= Utility::get_msb(result);

    for (size_t i = 0; i < size_of_vint - 1; ++i)
    {
        result = (result << 8) | stream.get();
    }

    return result;
}

template<bool value_with_vint_marker>
void EbmlVint<value_with_vint_marker>::write(std::ostream& stream, size_t encoded_length)
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
    if (!value_with_vint_marker)
    {
        encoded_value |= ((uint64_t)1 << (7 * encoded_length));
    }

    // Convert to big-endian
    char* encoded_bytes_ptr = reinterpret_cast<char*>(&encoded_value);
    std::reverse(encoded_bytes_ptr, encoded_bytes_ptr + encoded_length);

    // Write
    stream.write(encoded_bytes_ptr, encoded_length);
}

template<bool value_with_vint_marker>
std::ostream& operator<<(std::ostream& stream, EbmlVint<value_with_vint_marker> ebml_vint)
{
    ebml_vint.write(stream);
    return stream;
}