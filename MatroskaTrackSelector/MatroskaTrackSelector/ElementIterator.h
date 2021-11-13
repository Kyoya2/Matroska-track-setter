#pragma once
#include "EbmlElement.h"

class EbmlElement;

struct ElementIterator
{
    ElementIterator(BasicSharedPtr<EbmlElement>& parent);

    BasicSharedPtr<EbmlElement> operator*();
    ElementIterator& operator++();

    friend bool operator!=(const ElementIterator& current, uint64_t end_offset);

private:
    BasicSharedPtr<EbmlElement>& m_parent;
    BasicSharedPtr<EbmlElement> m_current_element;
};
/*
ElementIterator::ElementIterator(EbmlElement& parent) :
    m_parent(parent),
    m_current_element(nullptr)
{
    if (parent.get_length().get_value() != 0)
    {
        m_parent._seek_to(EbmlOffset::Data);
        m_current_element = std::make_shared<EbmlElement>(m_parent.m_stream);
    }
}

shared_ptr<EbmlElement> ElementIterator::operator*()
{
    return m_current_element;
}

ElementIterator& EbmlElement::ElementIterator::operator++()
{
    // Seek to end of last element and read
    m_current_element->_seek_to(EbmlOffset::End);
    m_current_element = std::make_shared<EbmlElement>(m_parent.m_stream);
    return *this;
}

bool operator!=(const ElementIterator& current, uint64_t end_offset)
{
    return (current.m_parent.get_length().get_value() != 0) && (current.m_current_element->end() != end_offset);
}*/