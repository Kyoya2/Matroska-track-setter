#pragma once

#include "Common.h"

class EbmlVint
{
public:
    explicit EbmlVint(uint64_t value);

private:
    uint64_t m_value;
};

