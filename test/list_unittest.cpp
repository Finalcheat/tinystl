#ifndef _LIST_UNITTEST_CPP_
#define _LIST_UNITTEST_CPP_ 1

#include "gtest/gtest.h"
#include "list.hpp"
#define TNS tinystl


namespace {

    TEST(list_test, list_constructor_test)
    {
        TNS::list<int> l1;
        ASSERT_TRUE(l1.empty());
        ASSERT_EQ(l1.begin(), l1.end());


        const size_t n2 = 5;
        TNS::list<int> l2(n2, 1);
        TNS::list<int>::const_iterator iter = l2.begin();
        for (size_t i = 0; i < n2; ++i)
        {
            ASSERT_EQ(*iter, 1);
            ++iter;
        }
        ASSERT_EQ(iter, l2.end());


        int arr3[] = {1, 2, 3, 4, 5};
        const size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
        TNS::list<int> l3(arr3, arr3 + n3);
        iter = l3.begin();
        for (size_t i = 0; i < n3; ++i)
        {
            ASSERT_EQ(*iter, arr3[i]);
            ++iter;
        }
        ASSERT_EQ(iter, l3.end());


        TNS::list<int> l4(l3);
        iter = l4.begin();
        for (size_t i = 0; i < n3; ++i)
        {
            ASSERT_EQ(*iter, arr3[i]);
            ++iter;
        }
        ASSERT_EQ(iter, l4.end());


        l4 = l2;
        iter = l4.begin();
        for (size_t i = 0; i < n2; ++i)
        {
            ASSERT_EQ(*iter, 1);
            ++iter;
        }
        ASSERT_EQ(iter, l4.end());
    }

    TEST(list_test, list_front_test)
    {
        TNS::list<int> l;
        ASSERT_EQ(l.begin(), l.end());

        l.push_front(1);
        ASSERT_EQ(l.front(), 1);

        l.push_front(2);
        l.push_front(3);
        TNS::list<int>::const_iterator iter = l.begin();
        ASSERT_EQ(*iter, 3);
        ++iter;
        ASSERT_EQ(*iter, 2);
        ++iter;
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(iter, l.end());

        l.pop_front();
        ASSERT_EQ(l.front(), 2);
        l.pop_front();
        ASSERT_EQ(l.front(), 1);
        l.pop_front();
        ASSERT_EQ(l.begin(), l.end());
        ASSERT_TRUE(l.empty());
    }

    TEST(list_test, list_back_test)
    {
        TNS::list<int> l;
        l.push_back(1);
        ASSERT_EQ(l.back(), 1);
        l.push_back(5);
        ASSERT_EQ(l.back(), 5);
        l.push_back(10);
        ASSERT_EQ(l.back(), 10);

        TNS::list<int>::iterator iter = l.begin();
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(*iter, 5);
        ++iter;
        ASSERT_EQ(*iter, 10);
        ++iter;
        ASSERT_EQ(iter, l.end());

        l.pop_back();
        ASSERT_EQ(l.back(), 5);
        l.pop_back();
        ASSERT_EQ(l.back(), 1);
        l.pop_back();
        ASSERT_EQ(l.begin(), l.end());
        ASSERT_TRUE(l.empty());
    }

    TEST(list_test, list_insert_test)
    {
        TNS::list<int> l;
        l.insert(l.end(), 1);
        ASSERT_EQ(l.front(), 1);
        ASSERT_EQ(l.back(), 1);

        l.insert(l.end(), 2);
        ASSERT_EQ(l.front(), 1);
        ASSERT_EQ(l.back(), 2);

        l.insert(l.begin(), 3);
        TNS::list<int>::const_iterator iter = l.begin();
        ASSERT_EQ(*iter, 3);
        ++iter;
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(*iter, 2);
        ++iter;
        ASSERT_EQ(iter, l.end());

        iter = l.begin();
        ++iter;
        ++iter;
        iter = l.insert(iter, 666);
        ASSERT_EQ(*iter, 666);
        iter = l.begin();
        ASSERT_EQ(*iter, 3);
        ++iter;
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(*iter, 666);
        ++iter;
        ASSERT_EQ(*iter, 2);
        ++iter;
        ASSERT_EQ(iter, l.end());

        int arr[] = {7, 8, 9};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::list<int> l2;
        l2.insert(l2.end(), arr, arr + n);
        iter = l2.begin();
        ASSERT_EQ(*iter++, 7);
        ASSERT_EQ(*iter++, 8);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(iter, l2.end());

        iter = l2.begin();
        ++iter;
        l2.insert(iter, arr + 1, arr + n);
        iter = l2.begin();
        ASSERT_EQ(*iter++, 7);
        ASSERT_EQ(*iter++, 8);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(*iter++, 8);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(iter, l2.end());
    }

    TEST(list_test, list_assign_test)
    {
        TNS::list<int> l1;
        l1.assign(3, 1);
        TNS::list<int>::const_iterator iter = l1.begin();
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(iter, l1.end());

        int arr[] = {2, 3, 4, 5, 6};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        l1.assign(arr, arr + n);
        iter = l1.begin();
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 3);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 5);
        ASSERT_EQ(*iter++, 6);
        ASSERT_EQ(iter, l1.end());
    }

    TEST(list_test, list_erase_test)
    {
        int arr1[] = {1, 2, 3, 4, 5};
        const size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
        TNS::list<int> l1;
        for (size_t i = 0; i < n1; ++i)
        {
            l1.push_back(arr1[i]);
        }

        TNS::list<int>::const_iterator iter = l1.begin();
        ++iter;
        ++iter;
        iter = l1.erase(iter);
        ASSERT_EQ(*iter, 4);

        iter = l1.begin();
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 5);
        ASSERT_EQ(iter, l1.end());

        --iter;
        iter = l1.erase(iter);
        ASSERT_EQ(iter, l1.end());
        iter = l1.begin();
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 4);

        iter = l1.begin();
        iter = l1.erase(iter);
        ASSERT_EQ(iter, l1.begin());
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(iter, l1.end());


        int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        const size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
        TNS::list<int> l2;
        for (size_t i = 0; i < n2; ++i)
        {
            l2.push_back(arr2[i]);
        }

        TNS::list<int>::const_iterator first = l2.begin();
        TNS::list<int>::const_iterator last = first;
        ++last;
        ++last;
        // erase [1, 3)
        iter = l2.erase(first, last);
        ASSERT_EQ(iter, l2.begin());
        ASSERT_EQ(*iter, 3);

        last = l2.end();
        first = last;
        --first;
        --first;
        --first;
        // erase [8, end())
        iter = l2.erase(first, last);
        ASSERT_EQ(iter, l2.end());
        ASSERT_EQ(l2.back(), 7);

        first = l2.begin();
        ++first;
        ++first;
        last = l2.end();
        --last;
        // erase [5, 7)
        iter = l2.erase(first, last);
        ASSERT_EQ(*iter, 7);
        iter = l2.begin();
        ASSERT_EQ(*iter++, 3);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 7);
        ASSERT_EQ(iter, l2.end());
    }

    TEST(list_test, list_swap_test)
    {
        const size_t n1 = 10;
        const size_t n2 = 20;
        TNS::list<int> l1(n1, 1);
        TNS::list<int> l2(n2, 2);

        l1.swap(l2);

        TNS::list<int>::const_iterator iter = l1.begin();
        for (size_t i = 0; i < n2; ++i)
        {
            ASSERT_EQ(*iter, 2);
            ++iter;
        }
        ASSERT_EQ(iter, l1.end());

        iter = l2.begin();
        for (size_t i = 0; i < n1; ++i)
        {
            ASSERT_EQ(*iter, 1);
            ++iter;
        }
        ASSERT_EQ(iter, l2.end());
    }

    TEST(list_test, list_resize_test)
    {
        TNS::list<int> l1;
        l1.resize(5);
        size_t i = 0;
        TNS::list<int>::iterator iter = l1.begin();
        for (; iter != l1.end(); ++iter)
        {
            ASSERT_EQ(*iter, 0);
            ++i;
        }
        ASSERT_EQ(i, 5);

        iter = l1.begin();
        *iter = 1;
        ++iter;
        *iter = 2;
        ++iter;
        *iter = 3;
        // l1 = [1, 2, 3, 0, 0]
        l1.resize(3);

        const int arr[] = {1, 2, 3};
        i = 0;
        iter = l1.begin();
        for (; iter != l1.end(); ++iter)
        {
            ASSERT_EQ(*iter, arr[i]);
            ++i;
        }
        ASSERT_EQ(i, 3);
        ASSERT_EQ(iter, l1.end());

        // repeat
        l1.resize(3);
        i = 0;
        iter = l1.begin();
        for (; iter != l1.end(); ++iter)
        {
            ASSERT_EQ(*iter, arr[i]);
            ++i;
        }
        ASSERT_EQ(i, 3);
        ASSERT_EQ(iter, l1.end());

        l1.resize(10, 666);
        iter = l1.begin();
        for (i = 0; i < 3; ++i)
        {
            ASSERT_EQ(*iter, arr[i]);
            ++iter;
        }
        for (; iter != l1.end(); ++iter)
        {
            ASSERT_EQ(*iter, 666);
            ++i;
        }
        ASSERT_EQ(i, 10);
        ASSERT_EQ(iter, l1.end());

        l1.resize(1, 888);
        iter = l1.begin();
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(iter, l1.end());
    }

    TEST(list_test, list_clear_test)
    {
        int arr[] = {1, 2, 3, 4, 5};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::list<int> l1;
        for (size_t i = 0; i < n; ++i)
        {
            l1.push_back(arr[i]);
        }

        TNS::list<int>::const_iterator iter = l1.begin();
        for (size_t i = 0; i < n; ++i)
        {
            ASSERT_EQ(*iter, arr[i]);
            ++iter;
        }

        l1.clear();
        ASSERT_TRUE(l1.empty());
        ASSERT_EQ(l1.begin(), l1.end());
    }

    TEST(list_test, list_remove_test)
    {
        int arr[] = {999, 67, 89, 45, 32, 45, 666};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::list<int> l1(arr, arr + n);
        // l1 = [999, 67, 89, 45, 32, 45, 666]
        l1.remove(999);
        // l1 = [67, 89, 45, 32, 45, 666]
        ASSERT_EQ(l1.front(), 67);

        l1.remove(45);
        // l1 = [67, 89, 32, 666]
        TNS::list<int>::const_iterator iter = l1.begin();
        ASSERT_EQ(*iter, 67);
        ++iter;
        ASSERT_EQ(*iter, 89);
        ++iter;
        ASSERT_EQ(*iter, 32);
        ++iter;
        ASSERT_EQ(*iter, 666);
        ++iter;
        ASSERT_EQ(iter, l1.end());

        TNS::list<int> l2(arr, arr + n);
        // l2 = [999, 67, 89, 45, 32, 45, 666]
        l2.remove_if([](int n) { return n % 2 != 0; });
        // l2 = [32, 666];
        iter = l2.begin();
        ASSERT_EQ(*iter, 32);
        ++iter;
        ASSERT_EQ(*iter, 666);
        ++iter;
        ASSERT_EQ(iter, l2.end());
    }

    TEST(list_test, list_unique_test)
    {
        int arr[] = {1, 2, 2, 3, 3, 2, 1, 1, 2};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::list<int> l1(arr, arr + n);
        l1.unique();
        // l1 = [1, 2, 3, 2, 1, 2]
        TNS::list<int>::const_iterator iter = l1.begin();
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(*iter, 2);
        ++iter;
        ASSERT_EQ(*iter, 3);
        ++iter;
        ASSERT_EQ(*iter, 2);
        ++iter;
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(*iter, 2);
        ++iter;
        ASSERT_EQ(iter, l1.end());

        TNS::list<int> l2(arr, arr + n);
        l2.unique([](const int a, const int b) { return a % 2 != b % 2; });
        // l2 = [1, 3, 3, 1, 1]
        iter = l2.begin();
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(*iter, 3);
        ++iter;
        ASSERT_EQ(*iter, 3);
        ++iter;
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(iter, l2.end());
    }

    TEST(list_test, list_merge_test)
    {
        int arr1[] = {0, 1, 2, 3, 4, 5, 9};
        const size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
        int arr2[] = {2, 4, 6, 8, 9, 9, 10, 12};
        const size_t n2 = sizeof(arr2) / sizeof(arr2[0]);

        TNS::list<int> l1(arr1, arr1 + n1);
        TNS::list<int> l2(arr2, arr2 + n2);

        l1.merge(l2);

        TNS::list<int>::const_iterator iter = l1.begin();
        ASSERT_EQ(*iter++, 0);
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 3);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 5);
        ASSERT_EQ(*iter++, 6);
        ASSERT_EQ(*iter++, 8);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(*iter++, 10);
        ASSERT_EQ(*iter++, 12);
        ASSERT_EQ(iter, l1.end());

        TNS::list<int> l3(arr1, arr1 + n1);
        TNS::list<int> l4(arr2, arr2 + n2);

        l3.merge(l4, [](const int a, const int b) { return a < b; });

        iter = l3.begin();
        ASSERT_EQ(*iter++, 0);
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 3);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 5);
        ASSERT_EQ(*iter++, 6);
        ASSERT_EQ(*iter++, 8);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(*iter++, 9);
        ASSERT_EQ(*iter++, 10);
        ASSERT_EQ(*iter++, 12);
        ASSERT_EQ(iter, l3.end());
    }

    TEST(list_test, list_reverse_test)
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::list<int> l(arr, arr + n);
        l.reverse();

        TNS::list<int>::const_iterator iter = l.begin();
        for (; iter != l.end(); ++iter)
        {
            --n;
            ASSERT_EQ(*iter, arr[n]);
        }
        ASSERT_EQ(n, 0);
    }

}


#endif
