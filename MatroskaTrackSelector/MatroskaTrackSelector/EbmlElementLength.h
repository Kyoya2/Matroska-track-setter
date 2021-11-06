#pragma once
#include <algorithm>

#include "Common.h"
#include "EbmlVintUtils.h"

class EbmlElementLength
{
public:
    EbmlElementLength(uint64_t value);
    explicit EbmlElementLength(std::istream& stream);

    EbmlElementLength(const EbmlElementLength& other) = default;
    EbmlElementLength& operator=(const EbmlElementLength& other) = default;

public:
    inline uint64_t get_value() { return m_value; }
    inline size_t get_minimal_encoded_size() { return m_minimal_encoded_size; }
    void write(std::ostream& stream, size_t encoded_length = 0);

private:
    uint64_t m_value;
    size_t m_minimal_encoded_size;
};