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
    inline EbmlElementLengthType get_value() { return m_value; }
    inline size_t get_minimal_encoded_size() { return m_minimal_encoded_size; }
    void write(std::ostream& stream, size_t encoded_length = 0);

private:
    EbmlElementLengthType m_value;
    size_t m_minimal_encoded_size;
};