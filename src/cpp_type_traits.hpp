#ifndef _TINYSTL_CPP_TYPE_TRAITS_HPP_
#define _TINYSTL_CPP_TYPE_TRAITS_HPP_ 1


namespace tinystl {

    struct __true_type {};
    struct __false_type {};


    template<bool>
    struct __truth_type
    {
        typedef __false_type __type;
    };


    template<>
    struct __truth_type<true>
    {
        typedef __true_type __type;
    };


    template<typename _Tp1, typename _Tp2>
    struct __traitor
    {
        enum { __value = bool(_Tp1::__value) || bool(_Tp2::__value) };
        typedef typename __truth_type<__value>::__type __type;
    };


    template<typename, typename>
    struct __are_same
    {
        enum { __value = 0 };
        typedef __false_type __type;
    };


    template<typename _Tp>
    struct __are_same<_Tp, _Tp>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<typename>
    struct ____is_void
    {
        enum { __value = 0 };
        typedef __false_type __type;
    };


    template<>
    struct ____is_void<void>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<typename>
    struct __is_integer
    {
        enum { __value = 0 };
        typedef __false_type __type;
    };


    template<>
    struct __is_integer<bool>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<char>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<signed char>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<unsigned char>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<short>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<unsigned short>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<int>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<unsigned int>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<long>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<unsigned long>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<long long>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_integer<unsigned long long>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<typename>
    struct __is_floating
    {
        enum { __value = 0 };
        typedef __false_type __type;
    };


    template<>
    struct __is_floating<float>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_floating<double>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<>
    struct __is_floating<long double>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<typename>
    struct ____is_pointer
    {
        enum { __value = 0 };
        typedef __false_type __type;
    };


    template<typename _Tp>
    struct ____is_pointer<_Tp*>
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<typename>
    struct __is_normal_iterator
    {
        enum { __value = 0 };
        typedef __false_type __type;
    };


    template<typename _Iterator>
    class __normal_iterator;


    template<typename _Iterator>
    struct __is_normal_iterator< tinystl::__normal_iterator<_Iterator> >
    {
        enum { __value = 1 };
        typedef __true_type __type;
    };


    template<typename _Tp>
    struct ____is_arithmetic : public __traitor< __is_integer<_Tp>, __is_floating<_Tp> >
    {};


    template<typename _Tp>
    struct ____is_scalar : public __traitor< ____is_arithmetic<_Tp>, ____is_pointer<_Tp> >
    {};

}


#endif
