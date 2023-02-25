/*   
 *   Matroska track setter  Copyright (C) 2023  Kyoya2
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
#ifdef _DEBUG
#define PRIVATE public
#else
#define PRIVATE private
#endif

#define NOMINMAX
#include <Windows.h>
#include <cassert>
#include <string>
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <functional>
#include <string_view>
#include <exception>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::string_view;
using std::reference_wrapper;
using std::pair;
using std::exception;

using Buffer = vector<uint8_t>;

#ifdef _DEBUG
#define DEBUG_PRINT(message) cout << message
#define DEBUG_PRINT_LINE(message) DEBUG_PRINT(message << endl)
#else
#define DEBUG_PRINT_LINE(message) 0
#define DEBUG_PRINT(message) 0
#endif

#define WriteLine(something) cout << something << endl

#define DECL_EXCEPTION(ex_name) \
struct ex_name                  \
{                               \
    ex_name() = default;        \
}

// Declare an exception object for each exception that can be displayed to the user, only high-level stuff.
DECL_EXCEPTION(InvalidMatroskaFile);
DECL_EXCEPTION(UnsupportedMatroskaFile);
DECL_EXCEPTION(InvalidRulesFileFormat);

namespace Utility
{
    inline uint64_t get_msb(uint64_t num);
    inline uint32_t get_msb(uint32_t num);
    inline size_t get_msb_index(uint64_t num);
    inline size_t get_byte_size(uint64_t num);
    inline uint64_t read_big_endian_from_stream(std::istream& stream, size_t length);
    inline void write_big_endian_to_stream(std::ostream& stream, uint64_t value, size_t encoded_length);
}

inline uint64_t Utility::get_msb(uint64_t num)
{
    if (0 == num)
        return 0;

    num = num >> 1;

    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num |= num >> 32;

    return num + 1;
}

inline uint32_t Utility::get_msb(uint32_t num)
{
    if (0 == num)
        return 0;

    num = num >> 1;

    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;

    return num + 1;
}

inline size_t Utility::get_msb_index(uint64_t num)
{
    unsigned long result;
    _BitScanReverse64(&result, num);
    return static_cast<size_t>(result);
}

inline size_t Utility::get_byte_size(uint64_t num)
{
    return (Utility::get_msb_index(num) / 8) + 1;
}

inline uint64_t Utility::read_big_endian_from_stream(std::istream& stream, size_t size)
{
    assert(size <= sizeof(uint64_t));

    if (0 == size)
        return 0;

    uint64_t result = 0;

    // Read as big-endian
    stream.read(reinterpret_cast<char*>(&result) + (sizeof(result) - size), size);

    // Convert to little-endian
    std::reverse(reinterpret_cast<char*>(&result), reinterpret_cast<char*>(&result + 1));
    return result;
}

inline void Utility::write_big_endian_to_stream(std::ostream& stream, uint64_t value, size_t encoded_length)
{
    assert(encoded_length <= sizeof(uint64_t));
    assert((get_msb_index(value) + 1) / 8 <= encoded_length);

    // Convert to big-endian
    char* encoded_bytes_ptr = reinterpret_cast<char*>(&value);
    std::reverse(encoded_bytes_ptr, encoded_bytes_ptr + encoded_length);

    stream.write(encoded_bytes_ptr, encoded_length);
}