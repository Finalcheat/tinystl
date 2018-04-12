#ifndef _TINYSTL_UNINITIALIZED_HPP_
#define _TINYSTL_UNINITIALIZED_HPP_ 1

#include "construct.hpp"
#include "cpp_type_traits.hpp"
#include "cstring.hpp"


namespace tinystl {


    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_aux(_InputIterator __first, _InputIterator __last,
                                                     _ForwardIterator __result, __true_type)
    {
        return tinystl::copy(__first, __last, __result);
    }


    template<typename _InputIterator, typename _ForwardIterator>
    _ForwardIterator __uninitialized_copy_aux(_InputIterator __first, _InputIterator __last,
                                              _ForwardIterator __result, __false_type)
    {
        _ForwardIterator __cur = __result;
        while (__first != __last)
        {
            tinystl::_Construct(&*__cur, *__first);
            ++__cur;
            ++__first;
        }
        return __cur;
    }


    template<typename _InputIterator, typename _ForwardIterator, typename _Allocator>
    _ForwardIterator __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
                                            _ForwardIterator __result, _Allocator __alloc)
    {
        _ForwardIterator __cur = __result;
        while (__first != __last)
        {
            __alloc.construct(&*__cur, *__first);
            ++__cur;
            ++__first;
        }
        return __cur;
    }


    template<typename _InputIterator, typename _ForwardIterator>
    _ForwardIterator uninitialized_copy(_InputIterator __first, _InputIterator __last,
                                        _ForwardIterator __result)
    {
        typedef typename tinystl::iterator_traits<_InputIterator>::value_type __Value_type;
        typedef typename tinystl::____is_scalar<__Value_type>::__type __Is_POD;
        return tinystl::__uninitialized_copy_aux(__first, __last, __result, __Is_POD());
    }


    inline char* uninitialized_copy(const char* __first, const char* __last, char* __result)
    {
        tinystl::memmove(__result, __first, __last - __first);
        return __result + (__last - __first);
    }


    inline wchar_t* uninitialized_copy(const wchar_t* __first, const wchar_t* __last, wchar_t* __result)
    {
        tinystl::memmove(__result, __first, sizeof(wchar_t) * (__last - __first));
        return __result + (__last - __first);
    }


    template<typename _ForwardIterator, typename _Tp>
    void __uninitialized_fill_aux(_ForwardIterator __first, _ForwardIterator __last,
                                  const _Tp& __x, __true_type)
    {
        return tinystl::fill(__first, __last, __x);
    }


    template<typename _ForwardIterator, typename _Tp>
    void __uninitialized_fill_aux(_ForwardIterator __first, _ForwardIterator __last,
                                  const _Tp& __x, __false_type)
    {
        _ForwardIterator __cur = __first;
        while (__cur != __last)
        {
            tinystl::_Construct(&*__cur, __x);
            ++__cur;
        }
    }


    template<typename _ForwardIterator, typename _Tp>
    void uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __x)
    {
        typedef typename iterator_traits<_ForwardIterator>::value_type _ValueType;
        typedef typename tinystl::____is_scalar<_ValueType>::__type _Is_POD;
        tinystl::__uninitialized_fill_aux(__first, __last, __x, _Is_POD());
    }


    template<typename _ForwardIterator, typename _Size, typename _Tp>
    void __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _Tp& __x, __true_type)
    {
        tinystl::fill_n(__first, __n, __x);
    }


    template<typename _ForwardIterator, typename _Size, typename _Tp>
    void __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _Tp& __x, __false_type)
    {
        _ForwardIterator __cur = __first;
        while (__n > 0)
        {
            tinystl::_Construct(&*__cur, __x);
            ++__cur;
            --__n;
        }
    }


    template<typename _ForwardIterator, typename _Size, typename _Tp>
    void uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
    {
        typedef typename iterator_traits<_ForwardIterator>::value_type _ValueType;
        typedef typename tinystl::____is_scalar<_ValueType>::__type _Is_POD;
        tinystl::__uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
    }


    template<typename _InputIterator, typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
                                                   _ForwardIterator __result, new_allocator<_Tp>)
    {
        return tinystl::uninitialized_copy(__first, __last, __result);
    }


    template<typename _ForwardIterator, typename _Tp1, typename _Tp2>
    inline void __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
                                       const _Tp1& __x, new_allocator<_Tp2>)
    {
        return tinystl::uninitialized_fill(__first, __last, __x);
    }


    template<typename _ForwardIterator, typename _Size, typename _Tp1, typename _Tp2>
    inline void __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
                                         const _Tp1& __x, new_allocator<_Tp2>)
    {
        return tinystl::uninitialized_fill_n(__first, __n, __x);
    }

}


#endif
