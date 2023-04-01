#pragma once
#include <unordered_set>

#include "Common.h"
#include "EbmlElementLength.h"

class EbmlElementBase;
using EbmlElementBasePtr = std::shared_ptr<EbmlElementBase>;

// Informatiuon relevant to all elements in a file
class EbmlDocumentInfoBlock
{
    EbmlDocumentInfoBlock(std::iostream& stream) : stream(stream), referenced_elements() {}

    std::iostream& stream;
    std::unordered_set<EbmlElementBase*> referenced_elements;
};
using EbmlDocumentInfoBlockPtr = std::shared_ptr<EbmlDocumentInfoBlock>;

// Offsets relative to the current element
enum class EbmlOffset
{
    Length, // Offset to the element's length
    Data,   // Offset to the element's data
    End     // Offset to the end of the element
};

class EbmlElementBase : public std::enable_shared_from_this<EbmlElementBase>
{
protected:
    // The stream pointer must be at the start of the element's length VINT
    EbmlElementBase(EbmlElementBasePtr parent);
    virtual ~EbmlElementBase() noexcept;

private:
    // Constructor for any element that doesn't have a paernt. Only 'EbmlDocument' is allowed to call this constructor
    // The stream pointer must be at the start of the element's length VINT
    EbmlElementBase(EbmlDocumentInfoBlockPtr info_block);

protected:
    inline constexpr size_t _get_offset(EbmlOffset what) const noexcept;
    std::iostream& _get_stream() const { return m_info->stream; }
    void _seek_stream(size_t offset) const { _get_stream().seekg(offset); }
    inline void seek_to(EbmlOffset where) const { _seek_stream(_get_offset(where)); }

    // TODO: restrict element visibility

    /*
    * It's important that 'm_data_length' is loaded before 'm_data_offset' bacause when we load
    * 'm_data_length', the stream pointer will be moved to the start of the element's data, which
    * is the value that needs to be loaded into 'm_data_offset'.
    *
    * The reasons that we store the offset to the element's data, and not, for example, the start
    * of the ID is that it's most likely that the most requested offset (from '_get_offset') would be
    * the offset to the element's data, that's because we need to know that offset each time
    * that we want to iterate over a master element's children, or to simply read a primitive
    * element's value. And because it's the most likely option to be requested, we want to be
    * able to return it as quickly as possible, without performing any calculations.
    */

protected:
    EbmlElementLength m_data_length;
private:
    size_t m_data_offset;    // The offset of the element's data
    EbmlElementBasePtr m_parent;
    EbmlDocumentInfoBlockPtr m_info;

    friend class EbmlDocument;
};

constexpr size_t EbmlElementBase::_get_offset(EbmlOffset what) const noexcept
{
    switch (what)
    {
    case EbmlOffset::Length:
        return m_data_offset - m_data_length.get_encoded_size();

    [[likely]]
    case EbmlOffset::Data:
        return m_data_offset;

    case EbmlOffset::End:
        return m_data_offset + m_data_length;

    [[unlikely]]
    default:
        return MAXSIZE_T;
    }
}