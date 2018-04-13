#ifndef _ARRAY_UNITTEST_CPP_
#define _ARRAY_UNITTEST_CPP_ 1

#include "gtest/gtest.h"
#include "array.hpp"
#define TNS tinystl


namespace {

    TEST(array_test, array_test_1)
    {
        const size_t len = 3;
        TNS::array<int, len> a1;
        ASSERT_EQ(a1.size(), len);

        a1[0] = 1;
        a1[1] = 2;
        a1[2] = 3;

        ASSERT_EQ(a1.size(), len);
        ASSERT_EQ(a1[0], 1);
        ASSERT_EQ(a1[1], 2);
        ASSERT_EQ(a1[2], 3);
        ASSERT_EQ(a1.front(), 1);
        ASSERT_EQ(a1.back(), 3);

        int* p = a1.data();
        ASSERT_EQ(*p, 1);
        ASSERT_EQ(*(p + 1), 2);
        ASSERT_EQ(*(p + 2), 3);

        TNS::array<int, len>::iterator iter = a1.begin();
        ASSERT_NE(iter, a1.end());

        int a2[len] = {1, 2, 3};
        p = a2;
        for (; iter != a1.end(); ++iter)
        {
            ASSERT_EQ(*iter, *p);
            ++p;
        }
    }

    TEST(array_test, array_test_2)
    {
        const size_t len = 3;
        TNS::array<int, len> a1{ {1, 2, 3} };
        TNS::array<int, len> a2 = {1, 2, 3};

        ASSERT_EQ(a1.size(), len);

        ASSERT_EQ(a1[0], 1);
        ASSERT_EQ(a1[1], 2);
        ASSERT_EQ(a1[2], 3);
        ASSERT_EQ(a1.front(), 1);
        ASSERT_EQ(a1.back(), 3);

        ASSERT_EQ(a2[0], 1);
        ASSERT_EQ(a2[1], 2);
        ASSERT_EQ(a2[2], 3);
        ASSERT_EQ(a2.front(), 1);
        ASSERT_EQ(a2.back(), 3);

        ASSERT_EQ(a1, a2);
    }

    TEST(array_test, array_test_3)
    {
        const size_t len = 5;
        TNS::array<int, len> a1{1, 2, 3, 4, 5};

        ASSERT_FALSE(a1.empty());
        ASSERT_EQ(a1.size(), 5);
        ASSERT_EQ(a1[0], 1);
        ASSERT_EQ(a1[1], 2);
        ASSERT_EQ(a1[2], 3);
        ASSERT_EQ(a1[3], 4);
        ASSERT_EQ(a1[4], 5);

        TNS::array<int, len> a2{6, 7, 8, 9, 10};
        a1.swap(a2);

        ASSERT_EQ(a1.size(), 5);
        ASSERT_EQ(a1[0], 6);
        ASSERT_EQ(a1[1], 7);
        ASSERT_EQ(a1[2], 8);
        ASSERT_EQ(a1[3], 9);
        ASSERT_EQ(a1[4], 10);
        ASSERT_EQ(a2.size(), 5);
        ASSERT_EQ(a2[0], 1);
        ASSERT_EQ(a2[1], 2);
        ASSERT_EQ(a2[2], 3);
        ASSERT_EQ(a2[3], 4);
        ASSERT_EQ(a2[4], 5);

        a1.fill(666);
        ASSERT_EQ(a1.size(), 5);
        for (const auto& v : a1)
        {
            ASSERT_EQ(v, 666);
        }

    }

}


#endif
