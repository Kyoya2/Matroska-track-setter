#include "EbmlElementBase.h"

EbmlElementBase::EbmlElementBase(std::iostream& stream) :
    m_info(std::make_shared<EbmlFileInfoBlock>(stream)),
    m_length_offset(stream.tellg()),
    m_data_length(stream),
    m_parent(nullptr)
{
    m_info->referenced_elements.emplace(this);
}

EbmlElementBase::EbmlElementBase(EbmlElementBasePtr parent) :
    m_info(parent->m_info),
    m_length_offset(m_info->stream.tellg()),
    m_data_length(m_info->stream),
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