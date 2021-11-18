#pragma once
#include <utility>
#include "Common.h"

/*
    This class is identical to std::share_pointer except it has a function that allows a pointer object to
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
private:
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
private:
    explicit BasicSharedPtr(Internal* internal_ptr);

public:
    // Default
    BasicSharedPtr();

    // Copy
    BasicSharedPtr(const BasicSharedPtr& other);
    BasicSharedPtr& operator=(const BasicSharedPtr& other);

    // Move
    BasicSharedPtr(BasicSharedPtr&& other) noexcept;
    BasicSharedPtr& operator=(BasicSharedPtr&& other) noexcept;
 
    // Dtor
    ~BasicSharedPtr();

    /******************************************************************************************************/
    /********************************************* Operators **********************************************/
    /******************************************************************************************************/
    inline T* operator->() { return &m_internal_ptr->obj; }
    inline T operator*() { return m_internal_ptr->obj; }

    /******************************************************************************************************/
    /************************************************ Misc ************************************************/
    /******************************************************************************************************/
    template <typename... Args>
    static BasicSharedPtr make_shared(Args&&... args) { return BasicSharedPtr(new Internal(std::forward<Args>(args)...)); }

    inline size_t get_refcount() { return m_internal_ptr->refcount; }

    inline bool is_null() { return nullptr == m_internal_ptr; }

    // Decreases refcount but doesn't invalidate object
    void release_ownership_unsafe();

private:
    Internal* m_internal_ptr;
    bool m_owned;
};

// Regular ctors
template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr(Internal* internal_ptr) :
    m_internal_ptr(internal_ptr),
    m_owned(true)
{}

template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr() :
    m_internal_ptr(nullptr),
    m_owned(false)
{}

// Copy
template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr(const BasicSharedPtr & other) :
    m_internal_ptr(other.m_internal_ptr),
    m_owned(true)
{
    ++m_internal_ptr->refcount;
}

template<typename T>
inline BasicSharedPtr<T>& BasicSharedPtr<T>::operator=(const BasicSharedPtr<T>& other)
{
    m_internal_ptr = other.m_internal_ptr;
    m_owned = true;
    ++m_internal_ptr->refcount;

    return *this;
}

// Move
template<typename T>
inline BasicSharedPtr<T>::BasicSharedPtr(BasicSharedPtr&& other) noexcept :
    m_internal_ptr(other.m_internal_ptr),
    m_owned(other.m_owned) // Although there's no reason to move non-owned objects, it's still possible
{
    other.m_owned = false;
    other.m_internal_ptr = nullptr;
}

template<typename T>
inline BasicSharedPtr<T>& BasicSharedPtr<T>::operator=(BasicSharedPtr<T>&& other) noexcept
{
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
        delete m_internal_ptr;
    }
}

template<typename T>
inline void BasicSharedPtr<T>::release_ownership_unsafe()
{
    if (get_refcount() > 1 && m_owned)
    {
        --m_internal_ptr->refcount;
        m_owned = false;
    }
    else
    {
        throw std::exception("Can't release ownership of single-owned object or can't release ownership twice");
    }
}
