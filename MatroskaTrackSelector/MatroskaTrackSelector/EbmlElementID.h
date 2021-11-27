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
    inline EbmlElementIDType get_value() const { return m_value; }
    inline size_t get_encoded_size() const { return m_encoded_size; }
    void write(std::ostream& stream) const;

    friend std::ostream& operator<<(std::ostream& stream, const EbmlElementID& element_id);
    friend std::istream& operator>>(std::istream& stream, EbmlElementID& element_id);

PRIVATE:
    size_t m_encoded_size;
    EbmlElementIDType m_value;
};