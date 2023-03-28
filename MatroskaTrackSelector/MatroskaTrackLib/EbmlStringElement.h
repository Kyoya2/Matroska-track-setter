#pragma once
#include "EbmlPrimitiveElement.h"

template <uint8_t id_size>
class EbmlStringElement : public EbmlPrimitiveElement<id_size, string>
{
protected:
    using EbmlPrimitiveElement<id_size, string>::EbmlPrimitiveElement;
    virtual ~EbmlStringElement() = default;

protected:
    virtual void _read_value(string& val) const override;
    virtual void _write_value(const string& value, size_t encoded_size) override;
    virtual constexpr size_t get_minimal_encoded_size(const string& val) override;
};

template <uint8_t id_size>
inline void EbmlStringElement<id_size>::_read_value(string& val) const
{
    val.resize(EbmlElementBase::m_data_length);
    EbmlElementBase::_read_content(val.data());
}

template <uint8_t id_size>
inline void EbmlStringElement<id_size>::_write_value(const string& value, size_t encoded_size)
{
    const size_t string_length = value.length();
    if (encoded_size < string_length)
        throw exception("The given string can't be encoded in the given size");

    // Note: it's not required to null-terminate strings inside EBML documents
    EbmlElementBase::_get_stream().write(value.data(), string_length);

    // if the encoded size of the string is bigger than the length of the string,
    // fill the remaining space with null-bytes.
    for (size_t i = string_length; i < encoded_size; ++i)
        EbmlElementBase::_get_stream().put('\0');
}

template <uint8_t id_size>
inline constexpr size_t EbmlStringElement<id_size>::get_minimal_encoded_size(const string& val)
{
    return val.length();
}
