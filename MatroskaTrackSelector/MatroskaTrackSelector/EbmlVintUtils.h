#pragma once
#include "Common.h"

namespace EbmlVintUtils
{
    static inline size_t get_minimal_encoded_size(uint64_t value, bool value_with_vint_marker)
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
        if (bit_count + byte_count <= byte_count * 8)
            return byte_count;
        else
            return byte_count + 1;
    }

    template<typename T>
    static inline T extract_from_stream(std::istream& stream, bool value_with_vint_marker, size_t* out_encoded_size = nullptr)
    {
        T result = stream.get();

        // Calculate the size of the VINT by calculating length of (VINT_WIDTH + VINT_DATA)
        size_t size_of_vint = 8 - Utility::get_msb_index(result);

        // Throw if the size is at more than 8 bytes
        if (size_of_vint > sizeof(T))
        {
            throw std::length_error("The given length is too big");
        }

        // Unset VINT_MARKER
        if (!value_with_vint_marker)
            result ^= Utility::get_msb(result);

        for (size_t i = 0; i < size_of_vint - 1; ++i)
        {
            result = (result << 8) | stream.get();
        }

        if (nullptr != out_encoded_size)
            *out_encoded_size = size_of_vint;

        return result;
    }

    static inline uint64_t remove_vint_marker(uint64_t value)
    {
        return value ^ Utility::get_msb(value);
    }

    static inline void encode_and_write(uint64_t value, size_t encoded_length, std::ostream& stream)
    {
        // Convert to big-endian
        char* encoded_bytes_ptr = reinterpret_cast<char*>(&value);
        std::reverse(encoded_bytes_ptr, encoded_bytes_ptr + encoded_length);

        // Write
        stream.write(encoded_bytes_ptr, encoded_length);
    }
}