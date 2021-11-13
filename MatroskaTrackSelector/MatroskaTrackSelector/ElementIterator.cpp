#include "ElementIterator.h"

ElementIterator::ElementIterator(BasicSharedPtr<EbmlElement>& parent) :
    m_current_element()
{
    if (parent->get_length().get_value() != 0)
    {
        m_current_element = parent->get_first_child();
    }
}

inline ElementIterator& ElementIterator::operator++()
{
    m_current_element = m_current_element->get_next_element();
    return *this;
}

inline BasicSharedPtr<EbmlElement> ElementIterator::operator*()
{
    return m_current_element;
}

inline bool ElementIterator::operator!=(void* ptr)
{
    ptr;
    return !m_current_element.is_null() && !m_current_element->is_last();
}