#pragma once
#include "UTCommon.h"
#include "BasicSharedPtr.h"

namespace BasicSharedPtrUT
{
    uint32_t regular_ctor_calls;
    uint32_t child_ctor_calls;
    uint32_t dtor_calls;

    class Test
    {
    public:
        Test() : m_parent(), m_self() { ++regular_ctor_calls; }
        Test(BasicSharedPtr<Test> parent) : m_parent(parent), m_self() { ++child_ctor_calls; }
        ~Test() { ++dtor_calls; }

        void set_self(BasicSharedPtr<Test> self)
        {
            m_self = self;
            m_self.release_ownership_unsafe();
        }
        BasicSharedPtr<Test> get_child()
        {
            BasicSharedPtr<Test> reult = BasicSharedPtr<Test>::make_shared(m_self);
            reult->set_self(reult);
            return reult;
        }

        BasicSharedPtr<Test> m_parent;
        BasicSharedPtr<Test> m_self;
    };

    void helper_func()
    {
        regular_ctor_calls = 0;
        dtor_calls = 0;
        BasicSharedPtr<Test> a = BasicSharedPtr<Test>::make_shared();
        CHECK(1 == regular_ctor_calls);
        CHECK(0 == dtor_calls);
        CHECK(1 == a.get_refcount());
        CHECK(nullptr == a->m_self.m_ptr);

        a->set_self(a);
        CHECK(1 == a.get_refcount());

        BasicSharedPtr<Test> b_1 = a->get_child();
        CHECK(2 == a.get_refcount());
        CHECK(1 == b_1.get_refcount());
        CHECK(b_1.m_ptr == b_1->m_self.m_ptr);

        BasicSharedPtr<Test> b_2 = a->get_child();
        CHECK(3 == a.get_refcount());
        CHECK(1 == b_2.get_refcount());
        CHECK(b_2.m_ptr == b_2->m_self.m_ptr);

        BasicSharedPtr<Test> c_1 = b_1->get_child();
        CHECK(3 == a.get_refcount());
        CHECK(2 == b_1.get_refcount());
        CHECK(c_1.m_ptr == c_1->m_self.m_ptr);
    }

    void run_tests()
    {
        helper_func();
        CHECK(1 == regular_ctor_calls);
        CHECK(4 == dtor_calls);
    }
}