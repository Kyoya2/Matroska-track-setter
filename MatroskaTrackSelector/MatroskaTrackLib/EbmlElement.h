#pragma once
#include <unordered_set>

#include "Common.h"
#include "EbmlElementBase.h"

// Offsets relative to the current element
enum class EbmlOffset
{
    Begin,                                 // Offset to the element ID
    Length = (int)EbmlBasicOffset::Length, // Offset to the element's length
    Data   = (int)EbmlBasicOffset::Data,   // Offset to the element's data
    End    = (int)EbmlBasicOffset::End     // Offset to the end of the element
};

template <uint8_t id_size>
class EbmlElement : public EbmlElementBase
{
protected:
    using EbmlElementBase::EbmlElementBase;

protected:
    inline constexpr size_t _get_offset(EbmlOffset what) const noexcept;
    inline void _seek_to(EbmlOffset where) const { _seek_stream(_get_offset(where)); }
};

template <uint8_t id_size>
constexpr size_t EbmlElement<id_size>::_get_offset(EbmlOffset what) const noexcept
{
    if (what == EbmlOffset::Begin)
        return _get_basic_offset(EbmlBasicOffset::Length) - id_size;
    else
        return _get_basic_offset(static_cast<EbmlBasicOffset>(what));
}