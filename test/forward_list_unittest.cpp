#ifndef _FORWARD_LIST_UNITTEST_CPP_
#define _FORWARD_LIST_UNITTEST_CPP_ 1

#include "gtest/gtest.h"
#include "forward_list.hpp"
#define TNS tinystl


namespace {

    TEST(forward_list_test, forward_list_test_1)
    {
        int arr[] = {1, 2, 3, 4, 5};
        int n = sizeof(arr) / sizeof(int);
        // ASSERT_EQ(n, 5);
        TNS::forward_list<int> f;
        for (int i = 0; i < n; ++i)
        {
            f.push_front(arr[i]);
        }

        TNS::forward_list<int>::iterator iter = f.begin();
        // ASSERT_EQ(*iter, 5);
        while (n-- > 0)
        {
            ASSERT_EQ(*iter, arr[n]);
            ++iter;
        }

        ASSERT_EQ(iter, f.end());

        n = sizeof(arr) / sizeof(int);
        iter = f.begin();
        for (; iter != f.end(); ++iter)
        {
            --n;
            ASSERT_EQ(*iter, arr[n]);
        }

        int& front = f.front();
        front = 9;

        ASSERT_EQ(*(f.begin()), 9);

        f.pop_front();
        ASSERT_EQ(*(f.begin()), 4);
    }

    TEST(forward_list_test, forward_list_test_2)
    {
        const size_t n = 5;
        TNS::forward_list<int> f(n);

        size_t i = 0;
        for (TNS::forward_list<int>::iterator iter = f.begin(); iter != f.end(); ++iter)
        {
            ASSERT_EQ(*iter, 0);
            ++i;
        }
        ASSERT_EQ(i, n);

        const int value = 6;
        TNS::forward_list<int> f2(n, value);
        size_t j = 0;
        for (TNS::forward_list<int>::iterator iter = f2.begin(); iter != f2.end(); ++iter)
        {
            ASSERT_EQ(*iter, value);
            ++j;
        }
        ASSERT_EQ(j, n);
    }

    TEST(forward_list_test, forward_list_test_3)
    {
        TNS::forward_list<int> f;

        TNS::forward_list<int>::const_iterator iter = f.before_begin();
        const int value = 99;
        TNS::forward_list<int>::const_iterator iter2 = f.insert_after(iter, value);
        ASSERT_EQ(*iter2, value);

        TNS::forward_list<int>::const_iterator iter3 = f.begin();
        ASSERT_EQ(*iter3, value);
        ASSERT_EQ(iter2, iter3);

        ++iter;
        ASSERT_EQ(iter, iter3);
        ++iter;
        ASSERT_EQ(iter, f.end());

        TNS::forward_list<int> f1;
        TNS::forward_list<int>::const_iterator iter4 = f1.before_begin();
        const size_t n = 3;
        const int value1 = 6;
        iter4 = f1.insert_after(iter4, n, value1);
        ASSERT_EQ(*iter4++, value1);
        ASSERT_EQ(iter4, f1.end());

        size_t i = 0;
        for (iter4 = f1.begin(); iter4 != f1.end(); ++iter4)
        {
            ASSERT_EQ(*iter4, value1);
            ++i;
        }
        ASSERT_EQ(i, n);
    }

    TEST(forward_list_test, forward_list_test_4)
    {
        int arr[] = {5, 4, 3, 2, 1};
        const size_t n = sizeof(arr) / sizeof(int);
        TNS::forward_list<int> f;
        for (size_t i = 0; i != n; ++i)
        {
            f.push_front(arr[i]);
        }

        // f = [1, 2, 3, 4, 5]
        TNS::forward_list<int>::const_iterator iter = f.begin();
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter, 2);
        // erase 3
        iter = f.erase_after(iter);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter, 5);
        iter = f.erase_after(iter);
        ASSERT_EQ(iter, f.end());

        iter = f.before_begin();
        // erase 1
        iter = f.erase_after(iter);
        ASSERT_EQ(*iter, 2);

        // f = [2, 4, 5]
        iter = f.begin();
        ASSERT_EQ(*iter++, 2);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 5);
        ASSERT_EQ(iter, f.end());

        TNS::forward_list<int> f1;
        for (size_t i = 0; i < n; ++i)
        {
            f1.push_front(arr[i]);
        }

        // f1 = [1, 2, 3, 4, 5]
        iter = f1.begin();
        ++iter;
        ++iter;
        ++iter;
        ASSERT_EQ(*iter, 4);

        // erase (1, 4)
        iter = f1.erase_after(f1.begin(), iter);
        ASSERT_EQ(*iter, 4);
        // f1 = [1, 4, 5]
        iter = f1.begin();
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(*iter++, 4);
        ASSERT_EQ(*iter++, 5);
        ASSERT_EQ(iter, f1.end());

        // erase (begin(), end())
        iter = f1.erase_after(f1.begin(), f1.end());
        // f1 = [1]
        ASSERT_EQ(iter, f1.end());
        iter = f1.begin();
        ASSERT_EQ(*iter++, 1);
        ASSERT_EQ(iter, f1.end());
    }

    TEST(forward_list_test, forward_list_test_5)
    {
        int arr[] = {5, 4, 3, 2, 1};
        size_t n = sizeof(arr) / sizeof(int);
        TNS::forward_list<int> f1;
        for (size_t i = 0; i < n; ++i)
        {
            f1.push_front(arr[i]);
        }

        // f1 = [1, 2, 3, 4, 5]
        TNS::forward_list<int> f2(f1);
        size_t i = 0;
        for (TNS::forward_list<int>::const_iterator iter = f2.begin(); iter != f2.end(); ++iter)
        {
            --n;
            ASSERT_EQ(*iter, arr[n]);
        }
        ASSERT_EQ(n, 0);

        TNS::forward_list<int> f3;
        f3.push_front(666);
        ASSERT_EQ(*(f3.begin()), 666);

        f3.clear();
        ASSERT_EQ(f3.begin(), f3.end());

        f3.push_front(777);
        ASSERT_EQ(*(f3.begin()), 777);

        f3 = f1;
        TNS::forward_list<int>::const_iterator f2_iter = f2.begin();
        for (TNS::forward_list<int>::const_iterator iter = f3.begin(); iter != f3.end(); ++iter)
        {
            ASSERT_EQ(*iter, *f2_iter);
            ++f2_iter;
        }
        ASSERT_EQ(f2_iter, f2.end());
    }

    TEST(forward_list_test, forward_list_test_6)
    {
        int arr[] = {1, 2, 3, 4, 5};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::forward_list<int> f(arr + 1, arr + 3);
        // f = [2, 3]
        TNS::forward_list<int>::const_iterator iter = f.begin();
        ASSERT_EQ(*iter, 2);
        ++iter;
        ASSERT_EQ(*iter, 3);
        ++iter;
        ASSERT_EQ(iter, f.end());
    }

    TEST(forward_list_test, forward_list_test_7)
    {
        TNS::forward_list<int> f1;
        const size_t n = 6;
        const int value = 666;
        f1.assign(n, value);
        // f1 = [666, 666, 666, 666, 666, 666]

        TNS::forward_list<int>::const_iterator iter = f1.begin();
        for (size_t i = 0; i < n; ++i)
        {
            ASSERT_EQ(*iter, value);
            ++iter;
        }
        ASSERT_EQ(iter, f1.end());

        TNS::forward_list<int> f2(1, 99);
        // f2 = [99]
        f2.push_front(88);
        // f2 = [88, 99]
        iter = f2.begin();
        f2.assign(n, *iter);
        // f2 = [88, 88, 88, 88, 88, 88]
        iter = f2.begin();
        for (size_t i = 0; i < n; ++i)
        {
            ASSERT_EQ(*iter, 88);
            ++iter;
        }
        ASSERT_EQ(iter, f2.end());

        TNS::forward_list<int> f3(10, value);
        f3.assign(n, 555);
        iter = f3.begin();
        for (size_t i = 0; i < n; ++i)
        {
            ASSERT_EQ(*iter, 555);
            ++iter;
        }
        for (size_t i = 0; i < (10 - n); ++i)
        {
            ASSERT_EQ(*iter, value);
            ++iter;
        }
        ASSERT_EQ(iter, f3.end());

        TNS::forward_list<int> f4;
        f4.assign(f3.begin(), f3.end());
        TNS::forward_list<int>::const_iterator f3_iter = f3.begin();
        for (iter = f4.begin(); iter != f4.end(); ++iter)
        {
            ASSERT_EQ(*iter, *f3_iter);
            ++f3_iter;
        }
        ASSERT_EQ(f3_iter, f3.end());

        int arr[] = {666, 777, 888, 999};
        f4.clear();
        // f4 = []
        f4.push_front(555);
        // f4 = [555]
        f4.assign(arr + 1, arr + 3);
        // f4 = [777, 888]
        iter = f4.begin();
        ASSERT_EQ(*iter++, 777);
        ASSERT_EQ(*iter++, 888);
        ASSERT_EQ(iter, f4.end());
    }

    TEST(forward_list_test, forward_list_test_8)
    {
        TNS::forward_list<int> f1;
        f1.resize(5);
        size_t i = 0;
        TNS::forward_list<int>::iterator iter = f1.begin();
        for (; iter != f1.end(); ++iter)
        {
            ASSERT_EQ(*iter, 0);
            ++i;
        }
        ASSERT_EQ(i, 5);

        iter = f1.begin();
        *iter = 1;
        ++iter;
        *iter = 2;
        ++iter;
        *iter = 3;
        // f1 = [1, 2, 3, 0, 0]
        f1.resize(3);

        const int arr[] = {1, 2, 3};
        i = 0;
        iter = f1.begin();
        for (; iter != f1.end(); ++iter)
        {
            ASSERT_EQ(*iter, arr[i]);
            ++i;
        }
        ASSERT_EQ(i, 3);
        ASSERT_EQ(iter, f1.end());

        // repeat
        f1.resize(3);
        i = 0;
        iter = f1.begin();
        for (; iter != f1.end(); ++iter)
        {
            ASSERT_EQ(*iter, arr[i]);
            ++i;
        }
        ASSERT_EQ(i, 3);
        ASSERT_EQ(iter, f1.end());

        f1.resize(10, 666);
        iter = f1.begin();
        for (i = 0; i < 3; ++i)
        {
            ASSERT_EQ(*iter, arr[i]);
            ++iter;
        }
        for (; iter != f1.end(); ++iter)
        {
            ASSERT_EQ(*iter, 666);
            ++i;
        }
        ASSERT_EQ(i, 10);
        ASSERT_EQ(iter, f1.end());

        f1.resize(1, 888);
        iter = f1.begin();
        ASSERT_EQ(*iter, 1);
        ++iter;
        ASSERT_EQ(iter, f1.end());
    }

    TEST(forward_list_test, forward_list_test_9)
    {
        int arr1[] = {1, 2, 3};
        const size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
        int arr2[] = {4, 5, 6, 7, 8};
        const size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
        TNS::forward_list<int> f1(arr1, arr1 + n1);
        TNS::forward_list<int> f2(arr2, arr2 + n2);

        TNS::forward_list<int>::const_iterator iter1 = f1.begin();
        ASSERT_EQ(*iter1, 1);
        ++iter1;
        ASSERT_EQ(*iter1, 2);
        ++iter1;
        ASSERT_EQ(*iter1, 3);
        ++iter1;
        ASSERT_EQ(iter1, f1.end());

        TNS::forward_list<int>::const_iterator iter2 = f2.begin();
        ASSERT_EQ(*iter2, 4);
        ++iter2;
        ASSERT_EQ(*iter2, 5);
        ++iter2;
        ASSERT_EQ(*iter2, 6);
        ++iter2;
        ASSERT_EQ(*iter2, 7);
        ++iter2;
        ASSERT_EQ(*iter2, 8);
        ++iter2;
        ASSERT_EQ(iter2, f2.end());

        f1.swap(f2);

        size_t i = 0;
        for (iter1 = f1.begin(); iter1 != f1.end(); ++iter1)
        {
            ASSERT_EQ(*iter1, arr2[i]);
            ++i;
        }
        ASSERT_EQ(i, n2);
        ASSERT_EQ(iter1, f1.end());

        i = 0;
        for (iter2 = f2.begin(); iter2 != f2.end(); ++iter2)
        {
            ASSERT_EQ(*iter2, arr1[i]);
            ++i;
        }
        ASSERT_EQ(i, n1);
        ASSERT_EQ(iter2, f2.end());
    }

    TEST(forward_list_test, forward_list_test_10)
    {
        int arr[] = {999, 67, 89, 45, 32, 45, 666};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::forward_list<int> f1(arr, arr + n);
        // f1 = [999, 67, 89, 45, 32, 45, 666]
        f1.remove(999);
        // f1 = [67, 89, 45, 32, 45, 666]
        ASSERT_EQ(f1.front(), 67);

        f1.remove(45);
        // f = [67, 89, 32, 666]
        TNS::forward_list<int>::const_iterator iter = f1.begin();
        ASSERT_EQ(*iter, 67);
        ++iter;
        ASSERT_EQ(*iter, 89);
        ++iter;
        ASSERT_EQ(*iter, 32);
        ++iter;
        ASSERT_EQ(*iter, 666);
        ++iter;
        ASSERT_EQ(iter, f1.end());

        TNS::forward_list<int> f2(arr, arr + n);
        // f2 = [999, 67, 89, 45, 32, 45, 666]
        f2.remove_if([](int n) { return n % 2 != 0; });
        // f2 = [32, 666];
        iter = f2.begin();
        ASSERT_EQ(*iter, 32);
        ++iter;
        ASSERT_EQ(*iter, 666);
        ++iter;
        ASSERT_EQ(iter, f2.end());
    }

    TEST(forward_list_test, forward_list_test_11)
    {
        int arr[] = {1, 2, 2, 3, 3, 2, 1, 1, 2};
        const size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::forward_list<int> f1(arr, arr + n);
        f1.unique();
        // f1 = [1, 2, 3, 2, 1, 2]
        TNS::forward_list<int>::const_iterator iter = f1.begin();
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
        ASSERT_EQ(iter, f1.end());

        TNS::forward_list<int> f2(arr, arr + n);
        f2.unique([](const int a, const int b) { return a % 2 != b % 2; });
        // f2 = [1, 3, 3, 1, 1]
        iter = f2.begin();
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
        ASSERT_EQ(iter, f2.end());
    }

    TEST(forward_list_test, forward_list_test_12)
    {
        int arr1[] = {0, 1, 2, 3, 4, 5, 9};
        const size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
        int arr2[] = {2, 4, 6, 8, 9, 9, 10, 12};
        const size_t n2 = sizeof(arr2) / sizeof(arr2[0]);

        TNS::forward_list<int> f1(arr1, arr1 + n1);
        TNS::forward_list<int> f2(arr2, arr2 + n2);

        f1.merge(f2);

        TNS::forward_list<int>::const_iterator iter = f1.begin();
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
        ASSERT_EQ(iter, f1.end());

        TNS::forward_list<int> f3(arr1, arr1 + n1);
        TNS::forward_list<int> f4(arr2, arr2 + n2);

        f3.merge(f4, [](const int a, const int b) { return a < b; });

        iter = f3.begin();
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
        ASSERT_EQ(iter, f3.end());
    }

    TEST(forward_list_test, forward_list_test_13)
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        size_t n = sizeof(arr) / sizeof(arr[0]);
        TNS::forward_list<int> f(arr, arr + n);
        f.reverse();

        TNS::forward_list<int>::const_iterator iter = f.begin();
        for (; iter != f.end(); ++iter)
        {
            --n;
            ASSERT_EQ(*iter, arr[n]);
        }
        ASSERT_EQ(n, 0);
    }

}


#endif
