#pragma once
#include "EbmlPrimitiveElement.h"
#include <bit>

// This is a wrapper for numeric primitive element types. This wrapper was created because
// reading / writing / calculating size of numeric elements is the same for all of them.
// 
// I use `std::bit_cast` to/from `uint64_t` so I can use the utility functions that are
// exclusive for `uint64_t` but don't really work differently with the rest of the numeric types
template <uint8_t id_size, typename T>
class EbmlNumericElement : public EbmlPrimitiveElement<id_size, T>
{
protected:
    using EbmlPrimitiveElement<id_size, T>::EbmlPrimitiveElement;
    virtual ~EbmlNumericElement() = default;

protected:
    virtual inline void _read_value(T& val) const override;
    virtual inline void _write_value(const T& value, size_t encoded_size) override;
    virtual inline constexpr size_t get_minimal_encoded_size(const T& val) override;
};

template <uint8_t id_size>
using EbmlIntElement   = EbmlNumericElement<id_size, int64_t>;
template <uint8_t id_size>
using EbmlUIntElement  = EbmlNumericElement<id_size, uint64_t>;
template <uint8_t id_size>
using EbmlFloatElement = EbmlNumericElement<id_size, double>;

template<uint8_t id_size, typename T>
inline void EbmlNumericElement<id_size, T>::_read_value(T& val) const
{
    val = std::bit_cast<T, uint64_t>(Utility::read_big_endian_from_stream(EbmlElementBase::_get_stream(), EbmlElementBase::m_data_length));
}

template<uint8_t id_size, typename T>
inline void EbmlNumericElement<id_size, T>::_write_value(const T& value, size_t encoded_size)
{
    Utility::write_big_endian_to_stream(
        EbmlElementBase::_get_stream(),
        std::bit_cast<uint64_t, T>(value),
        encoded_size
    );
}

template<uint8_t id_size, typename T>
inline constexpr size_t EbmlNumericElement<id_size, T>::get_minimal_encoded_size(const T& val)
{
    return Utility::get_byte_size(std::bit_cast<uint64_t, T>(val));
}
