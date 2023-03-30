#include "EbmlElementBase.h"

// Constructor for the EBML root, the stream pointer is at the start
// of the root element
EbmlElementBase::EbmlElementBase(std::iostream& stream) :
    m_info(std::make_shared<EbmlFileInfoBlock>(stream)),
    m_data_length(0),
    m_data_offset(stream.tellg()),
    m_parent(nullptr)
{
    m_info->referenced_elements.emplace(this);
}

// Constructor for the rest of the elements, the stream pointer is at
// the start of the element's length
EbmlElementBase::EbmlElementBase(EbmlElementBasePtr parent) :
    m_info(parent->m_info),
    m_data_length(m_info->stream),
    m_data_offset(m_info->stream.tellg()),
    m_parent(parent)
{
    m_info->referenced_elements.emplace(this);
}

EbmlElementBase::~EbmlElementBase() noexcept
{
    // If this dtor is called, then all of the reference to this object have been destroyed.
    // So now we can remove this from the set of referenced elements.
    m_info->referenced_elements.erase(this);
}