#ifndef _QUEUE_UNITTEST_CPP_
#define _QUEUE_UNITTEST_CPP_ 1

#include "gtest/gtest.h"
#include "queue.hpp"
#include "vector.hpp"
#define TNS tinystl


namespace {

    TEST(queue_test, queue_default_container_test)
    {
        TNS::queue<int> q;
        ASSERT_TRUE(q.empty());

        q.push(42);
        q.push(101);
        q.push(69);

        ASSERT_EQ(q.size(), 3);

        ASSERT_FALSE(q.empty());
        ASSERT_EQ(q.front(), 42);
        ASSERT_EQ(q.back(), 69);
        q.pop();
        ASSERT_EQ(q.front(), 101);
        ASSERT_EQ(q.back(), 69);
        q.pop();
        ASSERT_EQ(q.front(), 69);
        ASSERT_EQ(q.back(), 69);
        q.pop();
        ASSERT_TRUE(q.empty());
    }

}


#endif
