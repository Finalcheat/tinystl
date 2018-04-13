#ifndef _VECTOR_UNITTEST_CPP_
#define _VECTOR_UNITTEST_CPP_ 1

#include "gtest/gtest.h"
#include "vector.hpp"
#define TNS tinystl



namespace {

    TEST(vector_test, vec_test_1)
    {
        TNS::vector<int> v1;

        ASSERT_TRUE(v1.empty());
        ASSERT_EQ(v1.size(), 0);

        v1.push_back(42);

        ASSERT_EQ(v1.size(), 1);
        ASSERT_EQ(v1[0], 42);

        {
            TNS::vector< TNS::vector<int> > vect(10);
            TNS::vector< TNS::vector<int> >::iterator it(vect.begin());
            TNS::vector< TNS::vector<int> >::iterator end(vect.end());
            for (; it != end; ++it)
            {
                ASSERT_TRUE((*it).empty());
                ASSERT_EQ((*it).size(), 0);
                ASSERT_EQ((*it).capacity(), 0);
                ASSERT_EQ((*it).begin(), (*it).end());
            }
        }
    }


    TEST(vector_test, vec_test_2)
    {
        TNS::vector<double> v1;
        v1.push_back(32.1);
        v1.push_back(40.5);
        TNS::vector<double> v2;
        v2.push_back(3.56);

        ASSERT_EQ(v1.size(), 2);
        ASSERT_EQ(v1[0], 32.1);
        ASSERT_EQ(v1[1], 40.5);

        ASSERT_EQ(v2.size(), 1);
        ASSERT_EQ(v2[0], 3.56);

        const TNS::size_t v1Cap = v1.capacity();
        const TNS::size_t v2Cap = v2.capacity();

        v1.swap(v2);

        ASSERT_EQ(v1.size(), 1);
        ASSERT_EQ(v1.capacity(), v2Cap);
        ASSERT_EQ(v1[0], 3.56);

        ASSERT_EQ(v2.size(), 2);
        ASSERT_EQ(v2.capacity(), v1Cap);
        ASSERT_EQ(v2[0], 32.1);
        ASSERT_EQ(v2[1], 40.5);

        v2 = v1;

        ASSERT_EQ(v2.size(), 1);
        ASSERT_EQ(v2[0], 3.56);
    }


    TEST(vector_test, vec_test_3)
    {
        TNS::vector<char> v1;

        v1.push_back('h');
        v1.push_back('i');

        ASSERT_EQ(v1.size(), 2);
        ASSERT_EQ(v1[0], 'h');
        ASSERT_EQ(v1[1], 'i');

        TNS::vector<char> v2(v1.begin(), v1.end());
        v2[1] = 'o';

        ASSERT_EQ(v2.size(), 2);
        ASSERT_EQ(v2[0], 'h');
        ASSERT_EQ(v2[1], 'o');

        ASSERT_FALSE((v1 == v2));
        // ASSERT_TRUE((v1 < v2));
    }


    TEST(vector_test, vec_test_4)
    {
        TNS::vector<int> v(4);

        v[0] = 1;
        v[1] = 4;
        v[2] = 9;
        v[3] = 16;

        ASSERT_EQ(v.front(), 1);
        ASSERT_EQ(v.back(), 16);

        v.push_back(25);

        ASSERT_EQ(v.back(), 25);
        ASSERT_EQ(v.size(), 5);

        v.pop_back();

        ASSERT_EQ(v.back(), 16);
        ASSERT_EQ(v.size(), 4);
    }


    TEST(vector_test, vec_test_5)
    {
        int array[] = {1, 4, 9, 16};

        TNS::vector<int> v(array, array + 4);

        ASSERT_EQ(v.size(), 4);

        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 4);
        ASSERT_EQ(v[2], 9);
        ASSERT_EQ(v[3], 16);
    }


    TEST(vector_test, vec_test_6)
    {
        int array[] = {1, 4, 9, 16, 25, 36};

        TNS::vector<int> v(array, array + 6);
        TNS::vector<int>::iterator vit;

        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 4);
        ASSERT_EQ(v[2], 9);
        ASSERT_EQ(v[3], 16);
        ASSERT_EQ(v[4], 25);
        ASSERT_EQ(v[5], 36);

        vit = v.erase(v.begin());
        ASSERT_EQ(*vit, 4);

        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 4);
        ASSERT_EQ(v[1], 9);
        ASSERT_EQ(v[2], 16);
        ASSERT_EQ(v[3], 25);
        ASSERT_EQ(v[4], 36);

        vit = v.erase(v.end() - 1);
        ASSERT_EQ(vit, v.end());

        ASSERT_EQ(v.size(), 4);
        ASSERT_EQ(v[0], 4);
        ASSERT_EQ(v[1], 9);
        ASSERT_EQ(v[2], 16);
        ASSERT_EQ(v[3], 25);

        v.erase(v.begin() + 1, v.end() - 1);

        ASSERT_EQ(v.size(), 2);
        ASSERT_EQ(v[0], 4);
        ASSERT_EQ(v[1], 25);
    }


    TEST(vector_test, vec_test_7)
    {
        int array1[] = {1, 4, 25};
        int array2[] = {9, 16};

        TNS::vector<int> v(array1, array1 + 3);
        TNS::vector<int>::iterator vit;
        vit = v.insert(v.begin(), 0);
        ASSERT_EQ(*vit, 0);

        vit = v.insert(v.end(), 36);
        ASSERT_EQ(*vit, 36);

        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 0);
        ASSERT_EQ(v[1], 1);
        ASSERT_EQ(v[2], 4);
        ASSERT_EQ(v[3], 25);
        ASSERT_EQ(v[4], 36);

        v.insert(v.begin() + 3, array2, array2 + 2);

        ASSERT_EQ(v.size(), 7);
        ASSERT_EQ(v[0], 0);
        ASSERT_EQ(v[1], 1);
        ASSERT_EQ(v[2], 4);
        ASSERT_EQ(v[3], 9);
        ASSERT_EQ(v[4], 16);
        ASSERT_EQ(v[5], 25);
        ASSERT_EQ(v[6], 36);

        v.clear();
        ASSERT_TRUE(v.empty());

        v.insert(v.begin(), 5, 10);
        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 10);
        ASSERT_EQ(v[1], 10);
        ASSERT_EQ(v[2], 10);
        ASSERT_EQ(v[3], 10);
        ASSERT_EQ(v[4], 10);
    }


    struct TestStruct
    {
        unsigned int a[3];
    };


    TEST(vector_test, vec_capacity)
    {
        TNS::vector<int> v;

        ASSERT_EQ(v.capacity(), 0);
        v.push_back(42);
        ASSERT_GE(v.capacity(), 1);
        v.reserve(5000);
        ASSERT_GE(v.capacity(), 5000);
        ASSERT_EQ(v[0], 42);
        ASSERT_EQ(v.size(), 1);
    }


    TEST(vector_test, vec_at)
    {
        TNS::vector<int> v;
        TNS::vector<int> const& cv = v;

        v.push_back(10);
        ASSERT_EQ(v.at(0), 10);
        v.at(0) = 20;
        ASSERT_EQ(v.at(0), 20);
    }


    TEST(vector_test, vec_auto_ref)
    {
        TNS::vector<int> ref;
        for (size_t i = 0; i < 5; ++i)
        {
            ref.push_back(i);
        }

        TNS::vector< TNS::vector<int> > v_v_int(1, ref);
        v_v_int.push_back(v_v_int[0]);
        v_v_int.push_back(ref);
        v_v_int.push_back(v_v_int[0]);
        v_v_int.push_back(v_v_int[0]);
        v_v_int.push_back(ref);

        // TNS::vector< TNS::vector<int> >::const_iterator vvit = v_v_int.begin();
        TNS::vector< TNS::vector<int> >::iterator vvit = v_v_int.begin();
        // for (; vvit != v_v_int.end(); ++vvit)
        // {
        //     ASSERT_EQ(*vvit, ref);
        // }
    }


    TEST(vector_test, vec_assign_check)
    {
        TNS::vector<int> v(3, 1);
        ASSERT_EQ(v.size(), 3);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 1);
        ASSERT_EQ(v[2], 1);

        int array[] = {1, 2, 3, 4, 5};

        v.assign(array, array + 5);
        ASSERT_EQ(v[4], 5);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 2);
    }


    TEST(vector_test, vec_iterators)
    {
        TNS::vector<int> vint(10, 0);
        TNS::vector<int>& crvint = vint;

        ASSERT_EQ(vint.begin(), vint.begin());
        ASSERT_EQ(crvint.begin(), vint.begin());
        ASSERT_EQ(vint.begin(), crvint.begin());
        ASSERT_EQ(crvint.begin(), crvint.begin());

        ASSERT_NE(vint.begin(), vint.end());
        ASSERT_NE(crvint.begin(), vint.end());
        ASSERT_NE(vint.begin(), crvint.end());
        ASSERT_NE(crvint.begin(), crvint.end());

        ASSERT_EQ(vint.rbegin(), vint.rbegin());

        ASSERT_NE(vint.rbegin(), vint.rend());

        ASSERT_NE(crvint.rbegin(), crvint.rend());
    }

}


#endif
