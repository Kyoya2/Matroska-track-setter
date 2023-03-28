#include "EbmlMasterElement.h"

EbmlElementIterator::EbmlElementIterator(std::istream& stream, size_t first_child_offset, size_t parent_end_offset) :
    m_stream(stream),
    m_parent_end_offset(parent_end_offset),
    m_next_element_offset(first_child_offset),
    m_current_child_id(0)
{
    if (first_child_offset != parent_end_offset) [[likely]]
        _s_advance(stream, m_next_element_offset);

    // Otherwise, the child ID will remain 0, indicating that the end has been reached
}

EbmlElementIterator& EbmlElementIterator::operator++()
{
    // If the next element is withing the bounds of the parent, proceed normally
    if (m_next_element_offset < m_parent_end_offset) [[likely]]
        m_current_child_id = _s_advance(m_stream, m_next_element_offset);
    // If the next element is outside of the parent's bounds, indicate that the end has been reached
    else [[unlikely]]
        m_current_child_id = 0;

    return *this;
}

EbmlElementIDType EbmlElementIterator::_s_advance(std::istream& stream, size_t& inout_next_element_offset)
{
    size_t encoded_id_size = 0;
    size_t encoded_length_size = 0;

    stream.seekg(inout_next_element_offset);

    const EbmlElementIDType child_id = EbmlVintUtils::read_element_id_from_stream(stream, &encoded_id_size);

    // Calculate the offset to the next element, by adding the size of the current element to the
    // offset of the next element
    inout_next_element_offset += EbmlVintUtils::read_element_length_from_stream(stream, &encoded_length_size);

    // It's important that this statement is not combined with the above statement because the evaluation
    // order here is crucial, but C++ doesn't require a certain evaluation order when summing statements.
    inout_next_element_offset += encoded_id_size + encoded_length_size;

    return child_id;
}