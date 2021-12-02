#pragma once
#ifdef _DEBUG
#define PRIVATE public
#else
#define PRIVATE private
#endif

#include <cstdint>
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::array;
using std::shared_ptr;
using std::reference_wrapper;

using Buffer = vector<uint8_t>;

#ifdef _DEBUG
#define DEBUG_PRINT(message) cout << message << endl
#else
#define DEBUG_PRINT(message) 0
#endif

#define WriteLine(something) cout << something << endl

#define DECL_EXCEPTION(ex_name)                                                                    \
struct ex_name : public BaseMatroskaTrackSelectorException                                         \
{                                                                                                  \
    ex_name(const char* const message = nullptr) : BaseMatroskaTrackSelectorException(message) {}  \
}

struct BaseMatroskaTrackSelectorException
{
    BaseMatroskaTrackSelectorException(const char* const msg = nullptr) : message(msg) {}
    const char* const message;
};

DECL_EXCEPTION(SizeTooBigError);

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

    if (size > sizeof(uint64_t))
        throw SizeTooBigError();

    uint64_t result = stream.get();
    for (size_t i = 0; i < size - 1; ++i)
    {
        result = (result << 8) | stream.get();
    }
    return result;
}
