#pragma once
#include "EbmlElement.h"
#include <type_traits>

template <uint8_t id_size, typename T>
class EbmlPrimitiveElement : public EbmlElement<id_size>
{
    static_assert(std::is_default_constructible_v<T>); // Required for initializing this class before reading the actual value of the element
    static_assert(std::is_copy_assignable_v<T>);       // Required for assigning the newly-read value to the stored element

protected:
    EbmlPrimitiveElement(EbmlElementBasePtr parent);
    virtual ~EbmlPrimitiveElement() = default;
    
public:
    // The first call will read the value from the stream and store it, the rest of the calls will return
    // the stored value without reading
    const T& get_value() const;

    // It's the responsibility of the user to pass an encoded size that makes sense
    void set_value(const T& val, size_t encoded_size);

    // This function is not logically associatesd with an instance of this class,
    // it returns the minimal size to which the value can be encoded
    virtual constexpr size_t get_minimal_encoded_size(const T& val) = 0; // TODO: maybe remove this func

protected:
    // Populate `val` with data from the stream
    // When this function is called, the file pointer will be at the start of the element's data
    virtual void _read_value(T& val) const = 0;

    // Writes a value to the stream, Notes:
    // - This function should throw an exception in the case that the encoded size is too small .
    // - When this function is called, the file pointer will be at the start of the element's data
    virtual void _write_value(const T& value, size_t encoded_size) = 0;

    // Reads the contents of the current element into a given buffer
    void _read_content(void* buffer) const;

private:
    T m_value;
    bool m_is_initialized;
};

template <uint8_t id_size, typename T>
EbmlPrimitiveElement<id_size, T>::EbmlPrimitiveElement(EbmlElementBasePtr parent) :
    EbmlElement<id_size>(parent),
    m_value(),
    m_is_initialized(false)
{}

template <uint8_t id_size, typename T>
void EbmlPrimitiveElement<id_size, T>::_read_content(void* buffer) const
{
    EbmlElementBase::_basic_seek_to(EbmlOffset::Data);
    EbmlElementBase::_get_stream().read(reinterpret_cast<char*>(buffer), EbmlElementBase::m_data_length);
}

template <uint8_t id_size, typename T>
const T& EbmlPrimitiveElement<id_size, T>::get_value() const
{
    if (!m_is_initialized)
    {
        EbmlElementBase::_basic_seek_to(EbmlOffset::Data);
        _read_value(m_value);
        m_is_initialized = true;
    }

    return m_value;
}

template <uint8_t id_size, typename T>
void EbmlPrimitiveElement<id_size, T>::set_value(const T& value, size_t encoded_size)
{
    if (encoded_size != EbmlElementBase::m_data_length)
    {
        EbmlElementBase::_basic_seek_to(EbmlOffset::Length);
        EbmlElementBase::m_data_length = encoded_size;
        EbmlElementBase::_get_stream() << EbmlElement::m_data_length;
    }
    else
        EbmlElementBase::_basic_seek_to(EbmlOffset::Data);

    _write_value(value, encoded_size);
    m_value = value;
    m_is_initialized = true;
}