#pragma once
#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"

using EbmlElementSpecification = std::unordered_map<EbmlElementIDType, EbmlElementSpecification>;

template <const EbmlElementSpecification& element_specificaion>
class EbmlElement
{

private:
    EbmlElementID m_id;
    EbmlElementLength m_length;
    EbmlElement* m_parent;
    uint64_t m_position;
};