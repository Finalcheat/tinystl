#ifndef _ALGOBASE_UNITTEST_CPP_
#define _ALGOBASE_UNITTEST_CPP_ 1


#include "gtest/gtest.h"
#include "algobase.hpp"
#define TNS tinystl


namespace {

    TEST(algobase_test, swap)
    {
        int a = 1;
        int b = 2;
        TNS::swap(a, b);
        ASSERT_EQ(a, 2);
        ASSERT_EQ(b, 1);
    }


    TEST(algobase_test, iter_swap)
    {
        int array[6] = {0, 1, 2, 3, 4, 5};

        TNS::iter_swap(array, array + 3);

        ASSERT_EQ(array[0], 3);
        ASSERT_EQ(array[1], 1);
        ASSERT_EQ(array[2], 2);
        ASSERT_EQ(array[3], 0);
        ASSERT_EQ(array[4], 4);
        ASSERT_EQ(array[5], 5);
    }


    struct Student
    {
        Student(const int id, const float score) : _id(id), _score(score) { }
        int _id;
        int _score;
    };


    bool stuCmp(const Student& a, const Student& b)
    {
        if (a._score == b._score)
        {
            return a._id < b._id;
        }
        return a._score < b._score;
    }


    TEST(algobase_test, min)
    {
        int r = TNS::min(42, 100);
        ASSERT_EQ(r, 42);

        --r;
        r = TNS::min(r, r);
        ASSERT_EQ(r, 41);

        Student a(1, 90);
        Student b(2, 95);
        Student c(3, 95);

        Student s = TNS::min(a, b, stuCmp);
        ASSERT_EQ(s._id, 1);
        ASSERT_EQ(s._score, 90);

        s = TNS::min(a, c, stuCmp);
        ASSERT_EQ(s._id, 1);
        ASSERT_EQ(s._score, 90);

        s = TNS::min(b, c, stuCmp);
        ASSERT_EQ(s._id, 2);
        ASSERT_EQ(s._score, 95);
    }


    TEST(algobase_test, max)
    {
        int r = TNS::max(42, 100);
        ASSERT_EQ(r, 100);

        --r;
        r = TNS::min(r, r);
        ASSERT_EQ(r, 99);

        Student a(1, 90);
        Student b(2, 95);
        Student c(3, 95);

        Student s = TNS::max(a, b, stuCmp);
        ASSERT_EQ(s._id, 2);
        ASSERT_EQ(s._score, 95);

        s = TNS::max(a, c, stuCmp);
        ASSERT_EQ(s._id, 3);
        ASSERT_EQ(s._score, 95);

        s = TNS::max(c, b, stuCmp);
        ASSERT_EQ(s._id, 3);
        ASSERT_EQ(s._score, 95);
    }


    TEST(algobase_test, copy_array)
    {
        const int len = 23;
        char s[len] = "A string to be copied.";
        char result[len];
        TNS::copy(s, s + len, result);
        ASSERT_STREQ(result, s);
    }


    TEST(algobase_test, copy_volatile)
    {
        int a[] = {0, 1, 2, 3, 4, 5};
        const size_t len = sizeof(a) / sizeof(int);
        volatile int va[len];
        TNS::copy(a, a + len, va);
        for (size_t i = 0; i != len; ++i)
        {
            ASSERT_EQ(a[i], va[i]);
        }
    }


    TEST(algobase_test, copy_back_array)
    {
        const size_t len = 5;
        int n[len] = {1, 2, 3, 4, 5};
        int result[len];
        TNS::copy_backward(n, n + len, static_cast<int*>(result) + len);
        for (size_t i = 0; i != len; ++i)
        {
            ASSERT_EQ(n[i], result[i]);
        }
    }

}


#endif
