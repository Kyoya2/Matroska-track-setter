#pragma once
#include <algorithm>

#include "Common.h"
#include "EbmlVintUtils.h"

class EbmlElementID
{
public:
    EbmlElementID(uint64_t value);
    explicit EbmlElementID(std::istream& stream);

    EbmlElementID(const EbmlElementID& other) = default;
    EbmlElementID& operator=(const EbmlElementID& other) = default;

public:
    inline uint64_t get_value() { return m_value; }
    inline size_t get_encoded_size() { return m_encoded_size; }
    void write(std::ostream& stream);

private:
    uint64_t m_value;
    size_t m_encoded_size;
};