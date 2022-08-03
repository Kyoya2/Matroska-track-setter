/*   
 *   Matroska track setter  Copyright (C) 2022  Kyoya2
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
#include "UTCommon.h"
#include "BasicSharedPtr.h"

namespace BasicSharedPtrUT
{
    uint32_t regular_ctor_calls;
    uint32_t child_ctor_calls;
    uint32_t dtor_calls;
    uint32_t arg_ctor_calls;
    uint32_t arg_copy_ctor_calls;
    uint32_t arg_move_ctor_calls;

    class TestArg
    {
    public:
        TestArg() { ++arg_ctor_calls; };
        TestArg(const TestArg&) {++arg_copy_ctor_calls; }
        TestArg& operator=(const TestArg& other) = delete;
        TestArg(TestArg&&) noexcept { ++arg_move_ctor_calls; }
        TestArg& operator=(TestArg&& other) = delete;
    };

    class TestPointee
    {
    public:
        TestPointee(TestArg& ref) : m_parent(), m_self(), m_arg_ref(ref) { ++regular_ctor_calls; }
        TestPointee(BasicSharedPtr<TestPointee> parent) : m_parent(parent), m_self(), m_arg_ref(parent->m_arg_ref) { ++child_ctor_calls; }
        ~TestPointee() { ++dtor_calls; }

        void set_self(BasicSharedPtr<TestPointee> self)
        {
            m_self = self;
            m_self.release_ownership();
        }
        BasicSharedPtr<TestPointee> get_child()
        {
            BasicSharedPtr<TestPointee> reult = BasicSharedPtr<TestPointee>::make_basic_shared(m_self);
            reult->set_self(reult);
            return reult;
        }

        BasicSharedPtr<TestPointee> m_parent;
        BasicSharedPtr<TestPointee> m_self;
        TestArg& m_arg_ref;
    };

    void helper_func()
    {
        regular_ctor_calls = 0;
        child_ctor_calls = 0;
        dtor_calls = 0;
        arg_ctor_calls = 0;
        arg_copy_ctor_calls = 0;
        arg_move_ctor_calls = 0;

        TestArg qwe;
        CHECK(1 == arg_ctor_calls);

        BasicSharedPtr<TestPointee> a = BasicSharedPtr<TestPointee>::make_basic_shared(qwe);
        CHECK(1 == regular_ctor_calls);
        CHECK(0 == dtor_calls);
        CHECK(1 == a.get_refcount());
        CHECK(nullptr == a->m_self.m_internal_ptr);
        CHECK(0 == child_ctor_calls);

        CHECK(1 == arg_ctor_calls);
        CHECK(0 == arg_copy_ctor_calls);
        CHECK(0 == arg_move_ctor_calls);

        a->set_self(a);
        CHECK(1 == a.get_refcount());

        BasicSharedPtr<TestPointee> b_1 = a->get_child();
        CHECK(2 == a.get_refcount());
        CHECK(1 == b_1.get_refcount());
        CHECK(b_1.m_internal_ptr == b_1->m_self.m_internal_ptr);
        CHECK(1 == child_ctor_calls);

        BasicSharedPtr<TestPointee> b_2 = a->get_child();
        CHECK(3 == a.get_refcount());
        CHECK(1 == b_2.get_refcount());
        CHECK(b_2.m_internal_ptr == b_2->m_self.m_internal_ptr);
        CHECK(2 == child_ctor_calls);

        BasicSharedPtr<TestPointee> c_1 = b_1->get_child();
        CHECK(3 == a.get_refcount());
        CHECK(2 == b_1.get_refcount());
        CHECK(c_1.m_internal_ptr == c_1->m_self.m_internal_ptr);
        CHECK(3 == child_ctor_calls);
    }

    void run_tests()
    {
        helper_func();
        CHECK(1 == regular_ctor_calls);
        CHECK(4 == dtor_calls);
    }
}