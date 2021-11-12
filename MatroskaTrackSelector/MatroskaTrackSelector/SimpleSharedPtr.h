#pragma once
#include <utility>
#include "Common.h"

// Basically an implementation of 'shared_ptr' with the addition of the function 'release_ownership_unsafe'
template <typename T>
class SimpleSharedPtr
{
public:
    // regular ctor
    SimpleSharedPtr(T* ptr) :
        m_ptr(ptr),
        m_refcount_ptr(new size_t(1))
    {}

    // copy ctor
    SimpleSharedPtr(const SimpleSharedPtr& other) :
        m_ptr(other.m_ptr),
        m_refcount_ptr(other.m_refcount_ptr)
    {
        ++(*m_refcount_ptr);
    }
    SimpleSharedPtr& operator=(const SimpleSharedPtr& other)
    {
        m_ptr = other.m_ptr;
        m_refcount_ptr = other.m_refcount_ptr;
        ++(*m_refcount_ptr);
    }

    // move ctor
    SimpleSharedPtr(SimpleSharedPtr&& other) = delete;
    SimpleSharedPtr& operator=(SimpleSharedPtr&& other) = delete;
 
    // dtor
    ~SimpleSharedPtr()
    {
        if (0 == --(*m_refcount_ptr))
        {
            delete m_ptr;
            delete m_refcount_ptr;
        }
    }

    // operators
    T* operator->() { return m_ptr; }
    T operator*() { return *m_ptr; }

    // misc
    template <class... Args>
    static SimpleSharedPtr make_shared(Args&&... args)
    {
        return SimpleSharedPtr(new T(std::forward<Args>(args)...));
    }

    size_t get_refcount() { return *m_refcount_ptr; }

    // Decreases refcount but doesn't invalidate object
    void release_ownership_unsafe()
    {
        if (get_refcount() > 1)
            --(*m_refcount_ptr);
        else
            throw std::exception("Can't release ownership of single-owned object");
    }

private:
    T* m_ptr;
    size_t* m_refcount_ptr;
};