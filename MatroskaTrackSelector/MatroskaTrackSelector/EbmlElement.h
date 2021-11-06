#pragma once
#include "Common.h"
#include "EbmlElementID.h"
#include "EbmlElementLength.h"
#include "MatroskaElementSpecification.h"

enum class EbmlSeekPosition
{
    Header,
    Data,
    End
};

using EbmlElementSpecifications = std::unordered_map<EbmlElementIDType, EbmlElementSpecification>;

template <const EbmlElementSpecifications& element_specificaion>
class EbmlElement
{
    EbmlElement(std::iostream& stream, EbmlElement* parent) :
        m_stream(stream),
        m_offset(stream.tellg()),
        m_id(stream),
        m_length(stream),
        m_parent(parent)
    {}


private:
    inline void _seek_to(const EbmlSeekPosition seek_pos) const;

private:
    std::iostream& m_stream;
    uint64_t m_offset;
    EbmlElementID m_id;
    EbmlElementLength m_length;
    EbmlElement* m_parent;
};
