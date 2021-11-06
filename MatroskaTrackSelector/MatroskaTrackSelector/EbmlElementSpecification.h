#pragma once
#include "Common.h"

enum class EbmlElementType
{
    Master,
    Int,
    UInt,
    Float,
    AsciiString,
    Utf8,
    Date,
    Binary
};

struct EbmlElementSpecification
{
    const char* const name;
    const EbmlElementType element_type;
};

namespace EbmlElements
{
    std::unordered_map<uint64_t
}