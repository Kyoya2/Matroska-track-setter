#pragma once
#include "EbmlElementID.h"

class EbmlElementIterator
{
private:
    EbmlElementIterator(std::istream& stream, size_t first_child_offset, size_t parent_end_offset);

public:
    ~EbmlElementIterator() = default;

    EbmlElementIterator(const EbmlElementIterator&) = delete;
    EbmlElementIterator& operator=(const EbmlElementIterator&) = delete;

public:
    inline EbmlElementIDType get_current_child_id() const { return m_current_child_id; }

public:
    EbmlElementIterator& operator++();

    // Retunrs true as long as the current element is a child of the parent element.
    // When this returns false, calling any other member functions will yield incorrect results.
    operator bool() const { return m_current_child_id != 0; }

private:
    // Assumes that the stream pointer is at the start of an element.
    // inout_next_element_size should hold an offset to the current element, after this function
    // returns it will contain the offset to the next element. The function returns the ID of
    // the next element.
    static EbmlElementIDType _s_advance(std::istream& stream, size_t& inout_next_element_offset);
    void mark_end_reached() { m_current_child_id = 0; }

private:
    std::istream& m_stream;
    const size_t m_parent_end_offset;
    EbmlElementIDType m_current_child_id;
    size_t m_next_element_offset; // The offset to the ID of the next element

private:
    template <uint8_t id_size>
    friend class EbmlMasterElement;
};