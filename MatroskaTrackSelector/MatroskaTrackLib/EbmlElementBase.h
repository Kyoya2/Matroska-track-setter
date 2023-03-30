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
enum class EbmlOffset
{
    Length, // Offset to the element's length
    Data,   // Offset to the element's data
    End     // Offset to the end of the element
};

class EbmlElementBase : public std::enable_shared_from_this<EbmlElementBase>
{
protected:
    // When calling any contructor, the stream pointer must be at the end of the element's ID
    // and at the start of the elements length VINT.
    EbmlElementBase(EbmlElementBasePtr parent);
    virtual ~EbmlElementBase() noexcept;

private:
    // Only the EBML root element may be constructed using this constructor.
    // When calling any contructor, the stream pointer must be at the start of the root element
    EbmlElementBase(std::iostream& stream);

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
    * The reasons for storing the offset to the element's data, and not, for example, the start
    * of the ID are:
    * 
    *   1. It's most likely that the most requested offset (from '_get_offset') would be
    *      the offset to the element's data, that's because we need to know that offset each time
    *      that we want to iterate over a master element's children, or to simply read a primitive
    *      element's value. And because it's the most likely option to be requested, we want to be
    *      able to return it as quickly as possible, without performing any calculations.
    * 
    *   2. The EBML root is not actually an element, it doesn't have an ID or a length VINT. But
    *      I still want it to inherit from 'EbmlMasterElement' for the user's convenience. In order
    *      for the 'EbmlElementIterator' to work properly, we need to return '0' when it asks for
    *      for the root's data offset. This is only possible when the actual data offset is stored
    *      in the element. For example, if the element stores the offset to its length VINT, then
    *      the computation of its data offset would look something like this:
    * 
    *           data_offset = m_length_vint_offset + m_data_length.get_encoded_size();
    * 
    *      but the encoded size is always at-least 1, even when the value is 0. This means that we
    *      would get an incorrect result from '_get_offset' when requesting the data offset.
    */

protected:
    EbmlElementLength m_data_length;
private:
    size_t m_data_offset;    // The offset of the element's data
    EbmlElementBasePtr m_parent;
    EbmlFileInfoBlockPtr m_info;

    // TODO: friend class EbmlRoot; ???
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