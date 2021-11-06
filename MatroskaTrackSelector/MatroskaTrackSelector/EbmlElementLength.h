#pragma once
#include <algorithm>

#include "Common.h"
#include "EbmlVintUtils.h"

using EbmlElementLengthType = uint64_t;

class EbmlElementLength
{
public:
    EbmlElementLength(EbmlElementLengthType value);
    explicit EbmlElementLength(std::istream& stream);

    EbmlElementLength(const EbmlElementLength& other) = default;
    EbmlElementLength& operator=(const EbmlElementLength& other) = default;

public:
    inline EbmlElementLengthType get_value() const { return m_value; }
    inline size_t get_minimal_encoded_size() const { return m_minimal_encoded_size; }
    void write(std::ostream& stream, size_t encoded_length = 0) const;

    friend std::ostream& operator<<(std::ostream& stream, const EbmlElementLength& element_length);
    friend std::istream& operator>>(std::istream& stream, EbmlElementLength& element_length);

private:
    EbmlElementLengthType m_value;
    size_t m_minimal_encoded_size;
};