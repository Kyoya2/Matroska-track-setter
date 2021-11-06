#pragma once
#include <algorithm>

#include "Common.h"
#include "EbmlVintUtils.h"

using EbmlElementIDType = uint32_t;

class EbmlElementID
{
public:
    EbmlElementID(EbmlElementIDType value);
    explicit EbmlElementID(std::istream& stream);

    EbmlElementID(const EbmlElementID& other) = default;
    EbmlElementID& operator=(const EbmlElementID& other) = default;

public:
    inline EbmlElementIDType get_value() { return m_value; }
    inline size_t get_encoded_size() { return m_encoded_size; }
    void write(std::ostream& stream);

private:
    EbmlElementIDType m_value;
    size_t m_encoded_size;
};