#ifndef _TINYSTL_UNINITIALIZED_HPP_
#define _TINYSTL_UNINITIALIZED_HPP_ 1

#include "construct.hpp"
#include "cpp_type_traits.hpp"
#include "cstring.hpp"


namespace tinystl {


    /**
     *  @brief  复制[first, last)区间内容到[result, result + (last - first))
     *  @param  first       源区间开始
     *  @param  last        源区间结束
     *  @param  result      目标区间开始
     *  @return result + (last - first)
     *
     *  迭代器指向类型是POD，直接转调copy即可
     */
    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_aux(_InputIterator __first, _InputIterator __last,
                                                     _ForwardIterator __result, __true_type)
    {
        return tinystl::copy(__first, __last, __result);
    }


    /**
     *  @brief  复制[first, last)区间内容到[result, result + (last - first))
     *  @param  first       源区间开始
     *  @param  last        源区间结束
     *  @param  result      目标区间开始
     *  @return result + (last - first)
     *
     *  迭代器指向类型不是POD，遍历区间对每一个元素调用构造函数
     */
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


    /**
     *  @brief  复制[first, last)区间内容到[result, result + (last - first))
     *  @param  first       源区间开始
     *  @param  last        源区间结束
     *  @param  result      目标区间开始
     *  @param  alloc       内存分配器
     *  @return result + (last - first)
     */
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


    /**
     *  @brief  复制[first, last)区间内容到[result, result + (last - first))
     *  @param  first       源区间开始
     *  @param  last        源区间结束
     *  @param  result      目标区间开始
     *  @return result + (last - first)
     *
     *  判断是否是POD，转调上面两个函数之一
     */
    template<typename _InputIterator, typename _ForwardIterator>
    _ForwardIterator uninitialized_copy(_InputIterator __first, _InputIterator __last,
                                        _ForwardIterator __result)
    {
        typedef typename tinystl::iterator_traits<_InputIterator>::value_type __Value_type;
        typedef typename tinystl::____is_scalar<__Value_type>::__type __Is_POD;
        return tinystl::__uninitialized_copy_aux(__first, __last, __result, __Is_POD());
    }


    /**
     *  @brief  复制[first, last)区间内容到[result, result + (last - first))
     *  @param  first       源区间开始
     *  @param  last        源区间结束
     *  @param  result      目标区间开始
     *  @return result + (last - first)
     *
     *  特化，直接调用memmove
     */
    inline char* uninitialized_copy(const char* __first, const char* __last, char* __result)
    {
        tinystl::memmove(__result, __first, __last - __first);
        return __result + (__last - __first);
    }


    /**
     *  @brief  复制[first, last)区间内容到[result, result + (last - first))
     *  @param  first       源区间开始
     *  @param  last        源区间结束
     *  @param  result      目标区间开始
     *  @return result + (last - first)
     *
     *  特化，直接调用memmove
     */
    inline wchar_t* uninitialized_copy(const wchar_t* __first, const wchar_t* __last, wchar_t* __result)
    {
        tinystl::memmove(__result, __first, sizeof(wchar_t) * (__last - __first));
        return __result + (__last - __first);
    }


    /**
     *  @brief  将区间[first, last)填充内容x
     *  @param  first       区间开始
     *  @param  last        区间结束
     *  @param  x           填充值
     *  @return 无
     *
     *  迭代器指向类型是POD，直接转调fill即可
     */
    template<typename _ForwardIterator, typename _Tp>
    void __uninitialized_fill_aux(_ForwardIterator __first, _ForwardIterator __last,
                                  const _Tp& __x, __true_type)
    {
        return tinystl::fill(__first, __last, __x);
    }


    /**
     *  @brief  将区间[first, last)填充内容x
     *  @param  first       区间开始
     *  @param  last        区间结束
     *  @param  x           填充值
     *  @return 无
     *
     *  迭代器指向类型不是POD，遍历区间每一个元素调用构造函数
     */
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


    /**
     *  @brief  将区间[first, last)填充内容x
     *  @param  first       区间开始
     *  @param  last        区间结束
     *  @param  x           填充值
     *  @return 无
     *
     *  判断是否是POD，转调上面两个函数之一
     */
    template<typename _ForwardIterator, typename _Tp>
    void uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __x)
    {
        typedef typename iterator_traits<_ForwardIterator>::value_type _ValueType;
        typedef typename tinystl::____is_scalar<_ValueType>::__type _Is_POD;
        tinystl::__uninitialized_fill_aux(__first, __last, __x, _Is_POD());
    }


    /**
     *  @brief  将区间[first, first + n)填充内容x
     *  @param  first       区间开始
     *  @param  n           填充数量
     *  @param  x           填充值
     *  @return 无
     *
     *  迭代器指向类型是POD，直接转调fill_n即可
     */
    template<typename _ForwardIterator, typename _Size, typename _Tp>
    void __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _Tp& __x, __true_type)
    {
        tinystl::fill_n(__first, __n, __x);
    }


    /**
     *  @brief  将区间[first, first + n)填充内容x
     *  @param  first       区间开始
     *  @param  n           填充数量
     *  @param  x           填充值
     *  @return 无
     *
     *  迭代器指向类型不是POD，遍历区间每一个元素调用构造函数
     */
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


    /**
     *  @brief  将区间[first, first + n)填充内容x
     *  @param  first       区间开始
     *  @param  n           填充数量
     *  @param  x           填充值
     *  @return 无
     *
     *  判断是否是POD，转调上面两个函数之一
     */
    template<typename _ForwardIterator, typename _Size, typename _Tp>
    void uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
    {
        typedef typename iterator_traits<_ForwardIterator>::value_type _ValueType;
        typedef typename tinystl::____is_scalar<_ValueType>::__type _Is_POD;
        tinystl::__uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
    }


    /**
     *  @brief  复制[first, last)区间内容到[result, result + (last - first))
     *  @param  first       源区间开始
     *  @param  last        源区间结束
     *  @param  result      目标区间开始
     *  @return result + (last - first)
     *
     *  默认alloc，转调uninitialized_copy
     */
    template<typename _InputIterator, typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
                                                   _ForwardIterator __result, new_allocator<_Tp>)
    {
        return tinystl::uninitialized_copy(__first, __last, __result);
    }


    /**
     *  @brief  将区间[first, last)填充内容x
     *  @param  first       区间开始
     *  @param  last        区间结束
     *  @param  x           填充值
     *  @return 无
     *
     *  默认alloc，转调uninitialized_fill
     */
    template<typename _ForwardIterator, typename _Tp1, typename _Tp2>
    inline void __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
                                       const _Tp1& __x, new_allocator<_Tp2>)
    {
        return tinystl::uninitialized_fill(__first, __last, __x);
    }


    /**
     *  @brief  将区间[first, first + n)填充内容x
     *  @param  first       区间开始
     *  @param  n           填充数量
     *  @param  x           填充值
     *  @return 无
     *
     *  默认alloc，转调uninitialized_fill_n
     */
    template<typename _ForwardIterator, typename _Size, typename _Tp1, typename _Tp2>
    inline void __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
                                         const _Tp1& __x, new_allocator<_Tp2>)
    {
        return tinystl::uninitialized_fill_n(__first, __n, __x);
    }

}


#endif
