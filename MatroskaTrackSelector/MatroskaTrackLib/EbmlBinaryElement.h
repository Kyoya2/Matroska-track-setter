#pragma once
#include "EbmlPrimitiveElement.h"

// A binary element whose size is unknown at compile time
template <uint8_t id_size>
class EbmlBinaryElement : public EbmlPrimitiveElement<id_size, Buffer>
{
protected:
    using EbmlPrimitiveElement<id_size, Buffer>::EbmlPrimitiveElement;
    virtual ~EbmlBinaryElement() = default;

protected:
    virtual inline void _read_value(Buffer& val) const override;
    virtual inline void _write_value(const Buffer& value, size_t encoded_size) override;
    virtual inline constexpr size_t get_minimal_encoded_size(const Buffer& val) override;
};

template <uint8_t id_size>
inline void EbmlBinaryElement<id_size>::_read_value(Buffer& val) const
{
    val.resize(EbmlElementBase::m_data_length);
    EbmlElementBase::_read_content(val.data());
}

template <uint8_t id_size>
inline void EbmlBinaryElement<id_size>::_write_value(const Buffer& value, size_t encoded_size)
{
    const size_t buffer_size = value.size();
    if (encoded_size < buffer_size)
        throw exception("The given buffer can't be encoded in the given size");

    EbmlElementBase::_get_stream().write(reinterpret_cast<const char*>(value.data()), buffer_size);

    // if the encoded size of the buffer is bigger than the length of the buffer,
    // fill the remaining space with null-bytes.
    for (size_t i = buffer_size; i < encoded_size; ++i)
        EbmlElementBase::_get_stream().put('\0');
}

template <uint8_t id_size>
inline constexpr size_t EbmlBinaryElement<id_size>::get_minimal_encoded_size(const Buffer& val)
{
    return val.size();
}
