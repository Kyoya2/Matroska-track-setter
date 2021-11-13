#pragma once
#include "Common.h"
#include "EbmlElement.h"

class EbmlElement;

template <typename T>
class BasicSharedPtr;

class ElementIterator
{
public:
    ElementIterator(BasicSharedPtr<EbmlElement>& parent);

    inline ElementIterator& operator++();
    inline BasicSharedPtr<EbmlElement> operator*();

    inline bool operator!=(void* ptr);

private:
    BasicSharedPtr<EbmlElement> m_current_element;
};