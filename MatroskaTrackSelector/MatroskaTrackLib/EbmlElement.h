#pragma once
#include <unordered_set>

#include "Common.h"
#include "EbmlElementBase.h"

template <uint8_t id_size>
class EbmlElement : public EbmlElementBase
{
protected:
    using EbmlElementBase::EbmlElementBase;

protected:
    inline constexpr size_t _get_element_start_offset() const noexcept { return _get_basic_offset(EbmlBasicOffset::Length) - id_size; }
    inline void _seek_to_element_start() const { _seek_stream(_get_element_start_offset()); }
};