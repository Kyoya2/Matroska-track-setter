#pragma once
#include "UTCommon.h"

#define private public
#include "BasicSharedPtr.h"

namespace BasicSharedPtrUT
{
    uint32_t ctor_calls;
    uint32_t dtor_calls;

    class Test
    {
    public:
        Test(int a, int b) : m_a(a), m_b(b) { ++ctor_calls; }
        ~Test() { ++dtor_calls; }

        int m_a;
        int m_b;
    };

    void helper_func()
    {
        ctor_calls = 0;
        dtor_calls = 0;
        BasicSharedPtr<Test> a = BasicSharedPtr<Test>::make_shared(1, 2);
        CHECK(1 == a->m_a);
        CHECK(2 == a->m_b);
        CHECK(1 == ctor_calls);
        CHECK(0 == dtor_calls);
        CHECK(1 == a.get_refcount());

        BasicSharedPtr<Test> b = a;
        CHECK(b.m_ptr == a.m_ptr);
        CHECK(b.m_refcount_ptr == a.m_refcount_ptr);
        CHECK(1 == b->m_a);
        CHECK(2 == b->m_b);
        CHECK(1 == ctor_calls);
        CHECK(0 == dtor_calls);
        CHECK(2 == b.get_refcount());
    }

    void run_tests()
    {
        helper_func();
        CHECK(1 == ctor_calls);
        CHECK(1 == dtor_calls);
    }
}