#pragma once
#include "EbmlPrimitiveElement.h"

// A binary element whose size is known at compile time
template <uint8_t id_size, size_t buffer_size>
class EbmlFixedBinaryElement : public EbmlPrimitiveElement<id_size, FixedBuffer<buffer_size>>
{
protected:
    using EbmlPrimitiveElement<id_size, FixedBuffer<buffer_size>>::EbmlPrimitiveElement;
    virtual ~EbmlFixedBinaryElement() = default;

protected:
    virtual inline void _read_value(FixedBuffer<buffer_size>& val) const override;
    virtual inline void _write_value(const FixedBuffer<buffer_size>& value, size_t encoded_size) override;
    virtual inline constexpr size_t get_minimal_encoded_size(const FixedBuffer<buffer_size>& val) override;
};

template <uint8_t id_size, size_t buffer_size>
inline void EbmlFixedBinaryElement<id_size, buffer_size>::_read_value(FixedBuffer<buffer_size>& val) const
{
    EbmlPrimitiveElement<id_size, FixedBuffer<buffer_size>>::_read_content(val.data());
}

template <uint8_t id_size, size_t buffer_size>
inline void EbmlFixedBinaryElement<id_size, buffer_size>::_write_value(const FixedBuffer<buffer_size>& value, size_t encoded_size)
{
    if (encoded_size != buffer_size)
        throw exception("The given buffer can't be encoded in the given size");

    EbmlElementBase::_get_stream().write(reinterpret_cast<const char*>(value.data()), buffer_size);
}

template <uint8_t id_size, size_t buffer_size>
inline constexpr size_t EbmlFixedBinaryElement<id_size, buffer_size>::get_minimal_encoded_size(const FixedBuffer<buffer_size>&)
{
    return buffer_size;
}
