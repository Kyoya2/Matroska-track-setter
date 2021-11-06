#pragma once
#include "Common.h"
#include "EbmlElementID.h"

enum class EbmlElementType
{
    Master,
    Int,
    UInt,
    Float,
    AsciiString,
    Utf8String,
    Date,
    Binary
};

#pragma pack(push, 1)
struct EbmlElementSpecification
{
    const std::string_view name;
    const EbmlElementType element_type;
};
#pragma pack(pop)

namespace Matroska
{
    const std::unordered_map<EbmlElementIDType, EbmlElementSpecification> ELEMENTS
    {
{ELEMENTS}
    };

{ENUM_ELEMENTS}
}