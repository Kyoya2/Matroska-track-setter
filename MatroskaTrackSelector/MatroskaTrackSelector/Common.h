#pragma once
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::array;
using std::shared_ptr;

using Buffer = vector<uint8_t>;

#define WriteLine(something) cout << something << endl

namespace Utility
{
    inline uint64_t get_msb(uint64_t num);
    inline uint32_t get_msb(uint32_t num);
    inline size_t get_msb_index(uint64_t num);
    inline uint64_t read_big_endian_from_stream(std::istream& stream, size_t length);
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
    size_t msb_index = 0;
    while (0 != (num >>= 1)) ++msb_index;
    return msb_index;
}

inline uint64_t Utility::read_big_endian_from_stream(std::istream& stream, size_t size)
{
    if (0 == size)
        return 0;

    uint64_t result = stream.get();
    for (size_t i = 0; i < size - 1; ++i)
    {
        result = (result << 8) | stream.get();
    }
    return result;
}
