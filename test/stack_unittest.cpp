#ifndef _STACK_UNITTEST_CPP_
#define _STACK_UNITTEST_CPP_ 1

#include "gtest/gtest.h"
#include "stack.hpp"
#include "list.hpp"
#define TNS tinystl


namespace {

    TEST(stack_test, stack_default_container_test)
    {
        TNS::stack<int> s;
        ASSERT_TRUE(s.empty());

        s.push(42);
        s.push(101);
        s.push(69);

        ASSERT_EQ(s.size(), 3);

        ASSERT_FALSE(s.empty());
        ASSERT_EQ(s.top(), 69);
        s.pop();
        ASSERT_EQ(s.top(), 101);
        s.pop();
        ASSERT_EQ(s.top(), 42);
        s.pop();
        ASSERT_TRUE(s.empty());
    }

    TEST(stack_test, stack_list_container_test)
    {
        TNS::stack<int, TNS::list<int> > s;
        ASSERT_TRUE(s.empty());

        s.push(42);
        s.push(101);
        s.push(69);

        ASSERT_EQ(s.size(), 3);

        ASSERT_FALSE(s.empty());
        ASSERT_EQ(s.top(), 69);
        s.pop();
        ASSERT_EQ(s.top(), 101);
        s.pop();
        ASSERT_EQ(s.top(), 42);
        s.pop();
        ASSERT_TRUE(s.empty());
    }

}


#endif
