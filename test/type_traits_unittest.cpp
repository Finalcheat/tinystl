#ifndef _TYPE_TRAITS_UNITTEST_CPP_
#define _TYPE_TRAITS_UNITTEST_CPP_ 1


#include "gtest/gtest.h"
#include "cpp_type_traits.hpp"
#define TNS tinystl


namespace {

    bool type_to_bool(TNS::__true_type)
    {
        return true;
    }


    bool type_to_bool(TNS::__false_type)
    {
        return false;
    }


    TEST(type_traits_test, are_same)
    {
        int v = TNS::__are_same<int, int>::__value;
        bool b = type_to_bool(TNS::__are_same<int, int>::__type());
        ASSERT_EQ(v, 1);
        ASSERT_TRUE(b);

        v = TNS::__are_same<int, bool>::__value;
        b = type_to_bool(TNS::__are_same<int, bool>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, char>::__value;
        b = type_to_bool(TNS::__are_same<int, char>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, signed char>::__value;
        b = type_to_bool(TNS::__are_same<int, signed char>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, unsigned char>::__value;
        b = type_to_bool(TNS::__are_same<int, unsigned char>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, short>::__value;
        b = type_to_bool(TNS::__are_same<int, short>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, unsigned int>::__value;
        b = type_to_bool(TNS::__are_same<int, unsigned int>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, long>::__value;
        b = type_to_bool(TNS::__are_same<int, long>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, unsigned long>::__value;
        b = type_to_bool(TNS::__are_same<int, unsigned long>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, int&>::__value;
        b = type_to_bool(TNS::__are_same<int, int&>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, int*>::__value;
        b = type_to_bool(TNS::__are_same<int, int*>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, float>::__value;
        b = type_to_bool(TNS::__are_same<int, float>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<int, double>::__value;
        b = type_to_bool(TNS::__are_same<int, double>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<float, double>::__value;
        b = type_to_bool(TNS::__are_same<float, double>::__type());
        ASSERT_EQ(v, 0);
        ASSERT_FALSE(b);

        v = TNS::__are_same<float, float>::__value;
        b = type_to_bool(TNS::__are_same<float, float>::__type());
        ASSERT_EQ(v, 1);
        ASSERT_TRUE(b);

        v = TNS::__are_same<double, double>::__value;
        b = type_to_bool(TNS::__are_same<double, double>::__type());
        ASSERT_EQ(v, 1);
        ASSERT_TRUE(b);
    }


    TEST(type_traits_test, is_void)
    {
        int value = TNS::____is_void<int>::__value;
        bool b = type_to_bool(TNS::____is_void<int>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::____is_void<void>::__value;
        b = type_to_bool(TNS::____is_void<void>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);
    }


    TEST(type_traits_test, is_integer)
    {
        int value = TNS::__is_integer<int>::__value;
        bool b = type_to_bool(TNS::__is_integer<int>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<bool>::__value;
        b = type_to_bool(TNS::__is_integer<bool>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<char>::__value;
        b = type_to_bool(TNS::__is_integer<char>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<signed char>::__value;
        b = type_to_bool(TNS::__is_integer<signed char>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<unsigned char>::__value;
        b = type_to_bool(TNS::__is_integer<unsigned char>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<short>::__value;
        b = type_to_bool(TNS::__is_integer<short>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<unsigned short>::__value;
        b = type_to_bool(TNS::__is_integer<unsigned short>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<unsigned int>::__value;
        b = type_to_bool(TNS::__is_integer<unsigned int>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<long>::__value;
        b = type_to_bool(TNS::__is_integer<long>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<unsigned long>::__value;
        b = type_to_bool(TNS::__is_integer<unsigned long>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<long long>::__value;
        b = type_to_bool(TNS::__is_integer<long long>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<unsigned long long>::__value;
        b = type_to_bool(TNS::__is_integer<unsigned long long>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_integer<float>::__value;
        b = type_to_bool(TNS::__is_integer<float>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::__is_integer<double>::__value;
        b = type_to_bool(TNS::__is_integer<double>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::__is_integer<void>::__value;
        b = type_to_bool(TNS::__is_integer<void>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::__is_integer<int*>::__value;
        b = type_to_bool(TNS::__is_integer<int*>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);
    }


    TEST(type_traits_test, is_floating)
    {
        int value = TNS::__is_floating<int>::__value;
        bool b = type_to_bool(TNS::__is_floating<int>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::__is_floating<bool>::__value;
        b = type_to_bool(TNS::__is_floating<bool>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::__is_floating<float>::__value;
        b = type_to_bool(TNS::__is_floating<float>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_floating<double>::__value;
        b = type_to_bool(TNS::__is_floating<double>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::__is_floating<long double>::__value;
        b = type_to_bool(TNS::__is_floating<long double>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);
    }


    TEST(type_traits_test, is_pointer)
    {
        int value = TNS::____is_pointer<void*>::__value;
        bool b = type_to_bool(TNS::____is_pointer<void*>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_pointer<int*>::__value;
        b = type_to_bool(TNS::____is_pointer<int*>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_pointer<double*>::__value;
        b = type_to_bool(TNS::____is_pointer<double*>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_pointer<int**>::__value;
        b = type_to_bool(TNS::____is_pointer<int**>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_pointer<int>::__value;
        b = type_to_bool(TNS::____is_pointer<int>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);
    }


    TEST(type_traits_test, is_arithmetic)
    {
        int value = TNS::____is_arithmetic<int>::__value;
        bool b = type_to_bool(TNS::____is_arithmetic<int>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_arithmetic<bool>::__value;
        b = type_to_bool(TNS::____is_arithmetic<bool>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_arithmetic<double>::__value;
        b = type_to_bool(TNS::____is_arithmetic<double>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_arithmetic<void>::__value;
        b = type_to_bool(TNS::____is_arithmetic<void>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::____is_arithmetic<void*>::__value;
        b = type_to_bool(TNS::____is_arithmetic<void*>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);
    }


    TEST(type_traits_test, is_scalar)
    {
        int value = TNS::____is_scalar<void*>::__value;
        bool b = type_to_bool(TNS::____is_scalar<void*>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_scalar<void>::__value;
        b = type_to_bool(TNS::____is_scalar<void>::__type());
        ASSERT_EQ(value, 0);
        ASSERT_FALSE(b);

        value = TNS::____is_scalar<int>::__value;
        b = type_to_bool(TNS::____is_scalar<int>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_scalar<bool>::__value;
        b = type_to_bool(TNS::____is_scalar<bool>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_scalar<double>::__value;
        b = type_to_bool(TNS::____is_scalar<double>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);

        value = TNS::____is_scalar<int**>::__value;
        b = type_to_bool(TNS::____is_scalar<int**>::__type());
        ASSERT_EQ(value, 1);
        ASSERT_TRUE(b);
    }


}


#endif
