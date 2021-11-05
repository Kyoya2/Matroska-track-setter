#pragma once

#include "Common.h"

template<bool remove_vint_marker>
class EbmlVint
{
public:
    EbmlVint(uint64_t value);

    EbmlVint(const EbmlVint& other) = default;
    EbmlVint& operator=(const EbmlVint& other) = default;

public:
    inline uint64_t get_value() { return m_value; }

private:
    static inline uint64_t _s_remove_vint_marker(uint64_t value);
    inline size_t _s_get_minimal_encoded_size(uint64_t value);

// Members
private:
    uint64_t m_value;
    size_t m_minimal_encoded_size;
};

template<bool remove_vint_marker>
EbmlVint<remove_vint_marker>::EbmlVint(uint64_t value) :
    m_value(value),
    m_minimal_encoded_size(_s_get_minimal_encoded_size(value))
{}

template<bool remove_vint_marker>
inline uint64_t EbmlVint<remove_vint_marker>::_s_remove_vint_marker(uint64_t value)
{
    return value ^ Utility::get_msb(value);
}

template<bool remove_vint_marker>
inline size_t EbmlVint<remove_vint_marker>::_s_get_minimal_encoded_size(uint64_t value)
{
    if (0 == value)
        return 1;

    // The number of bits required to represent the number
    size_t bit_count = Utility::get_msb_index(value) + 1;

    // The number of bytes required to represent the number
    size_t byte_count = (bit_count / 8) + ((bit_count % 8 == 0) ? 0 : 1);

    // If the value already has the VINT_MARKER, the byte count is the minimal size
    if (!remove_vint_marker)
    {
        return byte_count;
    }

    // Check whether the number of bits with the addition of the bits for VINT_MARKER
    // can be stored using the same byte count
    if ((bit_count + byte_count) / 8 <= byte_count)
        return byte_count;
    else
        return byte_count + 1;
}
