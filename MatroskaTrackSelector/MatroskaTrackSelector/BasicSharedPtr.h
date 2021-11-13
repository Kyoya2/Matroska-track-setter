#pragma once
#include <utility>
#include "Common.h"

// Basically an implementation of 'shared_ptr' with the addition of the function 'release_ownership_unsafe'
template <typename T>
class BasicSharedPtr
{
    /******************************************************************************************************/
    /***************************************** (Con|De)structors ******************************************/
    /******************************************************************************************************/
private:
    BasicSharedPtr(T* ptr, size_t* refcount_ptr) :
        m_ptr(ptr),
        m_refcount_ptr(refcount_ptr),
        m_owned(true)
    {}

public:
    BasicSharedPtr() :
        m_ptr(nullptr),
        m_refcount_ptr(nullptr),
        m_owned(false)
    {}

    // Copy
    BasicSharedPtr(const BasicSharedPtr& other) :
        m_ptr(other.m_ptr),
        m_refcount_ptr(other.m_refcount_ptr),
        m_owned(true)
    {
        ++(*m_refcount_ptr);
    }
    BasicSharedPtr& operator=(const BasicSharedPtr& other)
    {
        m_ptr = other.m_ptr;
        m_refcount_ptr = other.m_refcount_ptr;
        m_owned = true;
        ++(*m_refcount_ptr);

        return *this;
    }

    // Move
    BasicSharedPtr(BasicSharedPtr&& other) noexcept :
        m_ptr(other.m_ptr),
        m_refcount_ptr(other.m_refcount_ptr),
        m_owned(other.m_owned) // Although there's no reason to move non-owned objects, it's still possible
    {
        other.m_owned = false;

        // This is not really necessary but I'll leave it for a while to find potential bugs
        other.m_ptr = nullptr;
        other.m_refcount_ptr = nullptr;
    }

    BasicSharedPtr& operator=(BasicSharedPtr&& other) noexcept
    {
        m_ptr = other.m_ptr;
        m_refcount_ptr = other.m_refcount_ptr;
        m_owned = other.m_owned; // Although there's no reason to move non-owned objects, it's still possible

        other.m_owned = false;
        // This is not really necessary but I'll leave it for a while to find potential bugs
        other.m_ptr = nullptr;
        other.m_refcount_ptr = nullptr;

        return *this;
    }
 
    // Dtor
    ~BasicSharedPtr()
    {
        if (m_owned &&
           (0 == --(*m_refcount_ptr)))
        {
            if (nullptr != m_ptr)
                delete m_ptr;
            delete m_refcount_ptr;
        }
    }

    /******************************************************************************************************/
    /********************************************* Operators **********************************************/
    /******************************************************************************************************/
    inline T* operator->() { return m_ptr; }
    inline T operator*() { return *m_ptr; }

    /******************************************************************************************************/
    /************************************************ Misc ************************************************/
    /******************************************************************************************************/
    template <class... Args>
    static BasicSharedPtr make_shared(Args&&... args)
    {
        return BasicSharedPtr(new T(std::forward<Args>(args)...), new size_t(1));
    }

    inline size_t get_refcount() { return *m_refcount_ptr; }

    inline bool is_null() { return nullptr == m_ptr; }

    // Decreases refcount but doesn't invalidate object
    void release_ownership_unsafe()
    {
        if (get_refcount() > 1 && m_owned)
        {
            --(*m_refcount_ptr);
            m_owned = false;
        }
        else
        {
            throw std::exception("Can't release ownership of single-owned object or can't release ownership twice");
        }
    }

private:
    T* m_ptr;
    size_t* m_refcount_ptr;
    bool m_owned;
};