/*   
 *   Matroska track setter  Copyright (C) 2021  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include "Common.h"

namespace EbmlVintUtils
{
    inline size_t get_minimal_encoded_size(uint64_t value, bool value_with_vint_marker);

    template<typename T>
    inline T extract_from_stream(std::istream& stream, bool value_with_vint_marker, size_t* out_encoded_size = nullptr);

    inline uint64_t remove_vint_marker(uint64_t value);
}

inline size_t EbmlVintUtils::get_minimal_encoded_size(uint64_t value, bool value_with_vint_marker)
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
inline T EbmlVintUtils::extract_from_stream(std::istream& stream, bool value_with_vint_marker, size_t* out_encoded_size)
{
    T result = stream.get();

    // Calculate the size of the VINT by calculating length of (VINT_WIDTH + VINT_DATA)
    size_t size_of_vint = 8 - Utility::get_msb_index(result);

    if (size_of_vint > sizeof(T))
    {
        throw exception("Value too big to parse");
    }

    // Unset VINT_MARKER
    if (!value_with_vint_marker)
        result ^= Utility::get_msb(result);

    // Read the rest of the VINT from the stream
    result <<= 8 * (size_of_vint - 1);
    result |= Utility::read_big_endian_from_stream(stream, size_of_vint - 1);

    if (nullptr != out_encoded_size)
        *out_encoded_size = size_of_vint;

    return result;
}

inline uint64_t EbmlVintUtils::remove_vint_marker(uint64_t value)
{
    return value ^ Utility::get_msb(value);
}