#pragma once
#include <unordered_set>

#include "Common.h"
#include "EbmlElementLength.h"

class EbmlElementBase;
using EbmlElementBasePtr = std::shared_ptr<EbmlElementBase>;

// Informatiuon relevant to all elements in a file
struct EbmlFileInfoBlock
{
    EbmlFileInfoBlock(std::iostream& stream) : stream(stream), referenced_elements() {}

    std::iostream& stream;
    std::unordered_set<EbmlElementBase*> referenced_elements;
};
using EbmlFileInfoBlockPtr = std::shared_ptr<EbmlFileInfoBlock>;

// Offsets relative to the current element
enum class EbmlBasicOffset
{
    Length, // Offset to the element's length
    Data,   // Offset to the element's data
    End     // Offset to the end of the element
};

class EbmlElementBase : public std::enable_shared_from_this<EbmlElementBase>
{
protected:
    // IMPORTANT: When calling any contructor, the stream pointer must be at the end of the element's ID
    // and at the start of the elements length VINT.
    // 
    // Only the root element may be constructed using this constructor
    EbmlElementBase(std::iostream& stream);
    EbmlElementBase(EbmlElementBasePtr parent);

    virtual ~EbmlElementBase() noexcept;

protected:
    inline constexpr size_t _get_basic_offset(EbmlBasicOffset what) const noexcept;
    std::iostream& _get_stream() const { return m_info->stream; }
    void _seek_stream(size_t offset) const { _get_stream().seekg(offset); }
    inline void _basic_seek_to(EbmlBasicOffset where) const { _seek_stream(_get_basic_offset(where)); }

    // TODO: restrict element visibility
private:
    EbmlFileInfoBlockPtr m_info;
protected:
    EbmlElementLength m_data_length;
private:
    size_t m_data_offset;    // The offset of the element's data
    EbmlElementBasePtr m_parent;

    // TODO: friend class EbmlRoot; ???
};

constexpr size_t EbmlElementBase::_get_basic_offset(EbmlBasicOffset what) const noexcept
{
    switch (what)
    {
    case EbmlBasicOffset::Length:
        return m_data_offset - m_data_length.get_encoded_size();

    case EbmlBasicOffset::Data:
        return m_data_offset;

    case EbmlBasicOffset::End:
        return m_data_offset + m_data_length;

    default:
        return MAXSIZE_T;
    }
}