/*   
 *   Matroska track setter  Copyright (C) 2023  Kyoya2
 *   
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include <utility>
#include "Common.h"

#ifdef _DEBUG
namespace BasicSharedPtrStats
{
    extern uint32_t total_creations;
    extern uint32_t total_deletions;
}
#endif

/*
    This class is identical to `std::shared_pointer` except it has a function that allows a pointer object to
    relinquish himself from ownership of the stored object while still allowing it to be copied validly.
    This is usefull for building dynamic trees that are stored on the heap:
    each node has a pointer of iteself which is not owned by himself, when it wants to create children it
    passes it's own pointer to the child who takes ownership of the object. when all of the children of a
    certain object are destroyed, the object itself will also be destroyed because although it holds a pointer
    to itself, it doesn't own it.
    Note that this example requires some static 'Create' function in that class that creates a node, sets their 
    own self-pointer and sets this pointer to an unowned state.
*/
template <typename T>
class BasicSharedPtr
{
PRIVATE:
    struct Internal
    {
        template <typename... Args>
        Internal(Args&&... args) :
            obj(std::forward<Args>(args)...),
            refcount(1)
        {}

        T obj;
        size_t refcount;
    };

    /******************************************************************************************************/
    /***************************************** (Con|De)structors ******************************************/
    /******************************************************************************************************/
PRIVATE:
    explicit BasicSharedPtr(Internal* internal_ptr);

public:
    BasicSharedPtr(std::nullptr_t ptr = nullptr);

    BasicSharedPtr(const BasicSharedPtr& other);
    BasicSharedPtr& operator=(const BasicSharedPtr& other);

    BasicSharedPtr(BasicSharedPtr&& other) noexcept;
    BasicSharedPtr& operator=(BasicSharedPtr&& other) noexcept;
 
    ~BasicSharedPtr();

    /******************************************************************************************************/
    /********************************************* Operators **********************************************/
    /******************************************************************************************************/
    inline T* operator->() { return &m_internal_ptr->obj; }
    inline T operator*() { return m_internal_ptr->obj; }

    inline const T* operator->() const { return &m_internal_ptr->obj; }

    inline operator bool() const { return !is_null(); }

    inline bool operator==(const BasicSharedPtr<T>& other) const { return m_internal_ptr == other.m_internal_ptr; }

    /******************************************************************************************************/
    /************************************************ Misc ************************************************/
    /******************************************************************************************************/
    template <typename... Args>
    static BasicSharedPtr make_basic_shared(Args&&... args);

    inline size_t get_refcount() const { return m_internal_ptr->refcount; }

    inline bool is_null() const { return nullptr == m_internal_ptr; }

    // Decreases refcount but doesn't invalidate object
    void release_ownership();

PRIVATE:
    Internal* m_internal_ptr;
    bool m_owned;
};

/******************************************************************************************************/
/***************************************** (Con|De)structors ******************************************/
/******************************************************************************************************/
// Regular ctors
template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr(Internal* internal_ptr) :
    m_internal_ptr(internal_ptr),
    m_owned(true)
{}

template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr(std::nullptr_t) :
    m_internal_ptr(nullptr),
    m_owned(false)
{}

// Copy
template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr(const BasicSharedPtr & other) :
    m_internal_ptr(other.m_internal_ptr),
    m_owned(nullptr != other.m_internal_ptr)
{
    // Increase the refcout only if the object is owned
    if (m_owned)
        ++m_internal_ptr->refcount;
}

template<typename T>
inline BasicSharedPtr<T>& BasicSharedPtr<T>::operator=(const BasicSharedPtr<T>& other)
{
    if (m_internal_ptr == other.m_internal_ptr)
        return *this;

    // Destroy current
    this->~BasicSharedPtr();

    m_internal_ptr = other.m_internal_ptr;
    m_owned = nullptr != other.m_internal_ptr;

    // Increase the refcout only if the object is owned
    if (m_owned)
        ++m_internal_ptr->refcount;

    return *this;
}

// Move
template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr(BasicSharedPtr&& other) noexcept :
    m_internal_ptr(other.m_internal_ptr),
    m_owned(other.m_owned)
{
    other.m_owned = false;
    other.m_internal_ptr = nullptr;
}

template<typename T>
inline BasicSharedPtr<T>& BasicSharedPtr<T>::operator=(BasicSharedPtr<T>&& other) noexcept
{
    if (m_internal_ptr == other.m_internal_ptr)
        return *this;

    // Destroy current
    this->~BasicSharedPtr();

    m_internal_ptr = other.m_internal_ptr;
    m_owned = other.m_owned; // Although there's no reason to move non-owned objects, it's still possible

    other.m_owned = false;
    other.m_internal_ptr = nullptr;

    return *this;
}

// Dtor
template<typename T>
inline BasicSharedPtr<T>::~BasicSharedPtr()
{
    if (m_owned &&
        (0 == --m_internal_ptr->refcount))
    {
#ifdef _DEBUG
        ++BasicSharedPtrStats::total_deletions;
#endif
        delete m_internal_ptr;
    }
}

/******************************************************************************************************/
/************************************************ Misc ************************************************/
/******************************************************************************************************/
template <typename T>
template <typename... Args>
static BasicSharedPtr<T> BasicSharedPtr<T>::make_basic_shared(Args&&... args)
{
#ifdef _DEBUG
    ++BasicSharedPtrStats::total_creations;
#endif
    return BasicSharedPtr(new Internal(std::forward<Args>(args)...));
}

template<typename T>
inline void BasicSharedPtr<T>::release_ownership()
{
    if (get_refcount() > 1 && m_owned)
    {
        --m_internal_ptr->refcount;
        m_owned = false;
    }
    else
    {
        throw exception("Can't release ownership of single-owned object or can't release ownership twice");
    }
}