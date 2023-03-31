#include "EbmlElementBase.h"

// Constructor for any element that doesn't have a paernt. Only 'EbmlDocument' is allowed to call this constructor
EbmlElementBase::EbmlElementBase(EbmlFileInfoBlockPtr info_block) :
    m_info(info_block),
    m_data_length(info_block->stream),
    m_data_offset(info_block->stream.tellg()),
    m_parent(nullptr)
{
    m_info->referenced_elements.emplace(this);
}

// Constructor for the rest of the elements
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