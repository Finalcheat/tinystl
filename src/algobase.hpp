#ifndef _TINYSTL_ALGOBASE_HPP_
#define _TINYSTL_ALGOBASE_HPP_ 1


#include "iterator_base_types.hpp"
#include "cstring.hpp"
#include "pair.hpp"


namespace tinystl {


    /**
     *  @brief 交换任意同类型的两个值
     *  @param  a 任意类型
     *  @param  b 任意类型
     *  @return 无
     */
    template<typename _Tp>
    inline void swap(_Tp& __a, _Tp& __b)
    {
        const _Tp __tmp = __a;
        __a = __b;
        __b = __tmp;
    }


    /**
     *  @brief 交换两个迭代器指向的内容
     *  @param  a 迭代器
     *  @param  b 迭代器
     *  @return 无
     *
     *  __iter_swap为对外接口iter_swap使用，__iter_swap目的是使用template技术特化达到编译器多态。
     */
    template<bool>
    struct __iter_swap
    {
        template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
            // 萃取出迭代器_ForwardIterator1指向的实际类型
            typedef typename iterator_traits<_ForwardIterator1>::value_type _ValueType1;
            const _ValueType1 __tmp = __a;
            __a = __b;
            __b = __tmp;
        }
    };


    /**
     *  @brief 交换两个迭代器指向的内容
     *  @param  a 迭代器
     *  @param  b 迭代器
     *  @return 无
     *
     *  全特化为true代表两个迭代器所指向的实际类型一致，直接调用swap交换。
     */
    template<>
    struct __iter_swap<true>
    {
        template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
            tinystl::swap(*__a, *__b);
        }
    };


    /**
     *  @brief 交换两个迭代器指向的内容
     *  @param  a 迭代器
     *  @param  b 迭代器
     *  @return 无
     */
    template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
    {
        // 萃取出迭代器_ForwardIterator1、_ForwardIterator2指向的类型和引用类型
        typedef typename iterator_traits<_ForwardIterator1>::value_type _ValueType1;
        typedef typename iterator_traits<_ForwardIterator2>::value_type _ValueType2;
        typedef typename iterator_traits<_ForwardIterator1>::reference  _ReferenceType1;
        typedef typename iterator_traits<_ForwardIterator2>::reference  _ReferenceType2;

        // 萃取类型判断是否相同
        const bool __type = __are_same<_ValueType1, _ValueType2>::__value &&
            __are_same<_ValueType1&, _ReferenceType1>::__value &&
            __are_same<_ValueType2&, _ReferenceType2>::__value;

        tinystl::__iter_swap<__type>::iter_swap(__a, __b);
    }


    /**
     *  @brief 返回较小的值
     *  @param  a 任意类型
     *  @param  b 任意类型
     *  @return 较小的值
     */
    template<typename _Tp>
    inline const _Tp& min(const _Tp& __a, const _Tp& __b)
    {
        if (__a < __b)
        {
            return __a;
        }
        return __b;
    }


    /**
     *  @brief 返回较小的值
     *  @param  a 任意类型
     *  @param  b 任意类型
     *  @param  comp 比较函数
     *  @return 较小的值
     */
    template<typename _Tp, typename _Compare>
    inline const _Tp& min(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
        if (__comp(__a, __b))
        {
            return __a;
        }
        return __b;
    }


    /**
     *  @brief 返回较大的值
     *  @param  a 任意类型
     *  @param  b 任意类型
     *  @return 较大的值
     */
    template<typename _Tp>
    inline const _Tp& max(const _Tp& __a, const _Tp& __b)
    {
        if (__a < __b)
        {
            return __b;
        }
        return __a;
    }


    /**
     *  @brief 返回较大的值
     *  @param  a 任意类型
     *  @param  b 任意类型
     *  @param  comp 比较函数
     *  @return 较大的值
     */
    template<typename _Tp, typename _Compare>
    inline const _Tp& max(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
        if (__comp(__a, __b))
        {
            return __b;
        }
        return __a;
    }


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  __copy为接口__copy_aux使用，__copy目的是使用template技术特化达到编译器多态。
     *  最通用的版本，遍历[first, last)拷贝
     */
    template<bool, typename>
    struct __copy
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
        {
            while (__first != __last)
            {
                *__result = *__first;
                ++__result;
                ++__first;
            }
            return __result;
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  输入迭代器是random_access_iterator_tag，先计算出需要拷贝的数量有助于编译器优化。
     */
    template<bool _BoolType>
    struct __copy<_BoolType, random_access_iterator_tag>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
        {
            typedef typename iterator_traits<_OutputIterator>::difference_type _Distance;
            for (_Distance __n = __last - __first; __n > 0; --__n)
            {
                *__result = *__first;
                ++__result;
                ++__first;
            }
            return __result;
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  输入输出是同一类型并且是指针，直接调用memmove。
     */
    template<>
    struct __copy<true, random_access_iterator_tag>
    {
        template<typename _Tp>
        static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
            tinystl::memmove(__result, __first, sizeof(_Tp) * (__last - __first));
            return __result + (__last - __first);
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  萃取输入输出类型，选取最好的__copy版本调用。
     */
    template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator __copy_aux(_InputIterator __first, _InputIterator __last,
                                      _OutputIterator __result)
    {
        typedef typename iterator_traits<_InputIterator>::value_type         _ValueTypeI;
        typedef typename iterator_traits<_OutputIterator>::value_type        _ValueTypeO;
        typedef typename iterator_traits<_OutputIterator>::iterator_category _CategoryO;
        const bool __sample = ____is_scalar<_ValueTypeI>::__value &&
            ____is_pointer<_InputIterator>::__value &&
            ____is_pointer<_OutputIterator>::__value &&
            __are_same<_ValueTypeI, _ValueTypeO>::__value;

        return tinystl::__copy<__sample, _CategoryO>::copy(__first, __last, __result);
    }


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  通用版本，输入输出都不是normal迭代器。
     */
    template<bool, bool>
    struct __copy_normal
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
        {
            return tinystl::__copy_aux(__first, __last, __result);
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  输入是normal迭代器，输出不是normal迭代器
     */
    template<>
    struct __copy_normal<true, false>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
        {
            return _OutputIterator(tinystl::__copy_aux(__first.base(), __last.base(), __result));
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  输入不是normal迭代器，输出是normal迭代器
     */
    template<>
    struct __copy_normal<false, true>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
        {
            return _OutputIterator(tinystl::__copy_aux(__first, __last, __result.base()));
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     *
     *  输入输出都是normal迭代器
     */
    template<>
    struct __copy_normal<true, true>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
        {
            return _OutputIterator(tinystl::__copy_aux(__first.base(), __last.base(), __result.base()));
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result + (last - first)
     */
    template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
    {
        const bool __in  = __is_normal_iterator<_InputIterator>::__value;
        const bool __out = __is_normal_iterator<_OutputIterator>::__value;
        return _OutputIterator(tinystl::__copy_normal<__in, __out>::copy(__first, __last, __result));
    }


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     */
    template<bool, typename>
    struct __copy_backward
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy_b(_InputIterator __first, _InputIterator __last,
                                      _OutputIterator __result)
        {
            while (__first != __last)
            {
                --__result;
                --__last;
                *__result = *__last;
            }
            return __result;
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     *
     *  输入迭代器是random_access_iterator_tag，计算出循环次数有助于编译器优化。
     */
    template<bool _BoolType>
    struct __copy_backward<_BoolType, random_access_iterator_tag>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy_b(_InputIterator __first, _InputIterator __last,
                                      _OutputIterator __result)
        {
            typename iterator_traits<_InputIterator>::difference_type __n;
            for (__n = __last - __first; __n > 0; --__n)
            {
                --__result;
                --__last;
                *__result = *__last;
            }
            return __result;
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     *
     *  输入类型一样并且是指针，直接调用memmove。
     */
    template<>
    struct __copy_backward<true, random_access_iterator_tag>
    {
        template<typename _Tp>
        static _Tp* copy_b(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
            const ptrdiff_t __n = __last - __first;
            tinystl::memmove(__result - __n, __first, sizeof(_Tp) * __n);
            return __result - __n;
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     */
    template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator __copy_backward_aux(_InputIterator __first, _InputIterator __last,
                                               _OutputIterator __result)
    {
        typedef typename iterator_traits<_InputIterator>::value_type         _ValueTypeI;
        typedef typename iterator_traits<_OutputIterator>::value_type        _ValueTypeO;
        typedef typename iterator_traits<_OutputIterator>::iterator_category _CategoryO;
        const bool __sample = ____is_scalar<_ValueTypeI>::__value &&
            ____is_pointer<_InputIterator>::__value &&
            ____is_pointer<_OutputIterator>::__value &&
            __are_same<_ValueTypeI, _ValueTypeO>::__value;

        return tinystl::__copy_backward<__sample, _CategoryO>::copy_b(__first, __last, __result);
    }


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     *
     *  通用版本，输入输出都不是normal迭代器。
     */
    template<bool, bool>
    struct __copy_backward_normal
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy_b(_InputIterator __first, _InputIterator __last,
                                      _OutputIterator __result)
        {
            return tinystl::__copy_backward_aux(__first, __last, __result);
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     *
     *  输入是normal迭代器，输出不是normal迭代器。
     */
    template<>
    struct __copy_backward_normal<true, false>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy_b(_InputIterator __first, _InputIterator __last,
                                      _OutputIterator __result)
        {
            return _OutputIterator(tinystl::__copy_backward_aux(__first.base(), __last.base(), __result));
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     *
     *  输入不是normal迭代器，输出是normal迭代器。
     */
    template<>
    struct __copy_backward_normal<false, true>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy_b(_InputIterator __first, _InputIterator __last,
                                      _OutputIterator __result)
        {
            return _OutputIterator(tinystl::__copy_backward_aux(__first, __last, __result.base()));
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     *
     *  输入输出都是normal迭代器。
     */
    template<>
    struct __copy_backward_normal<true, true>
    {
        template<typename _InputIterator, typename _OutputIterator>
        static _OutputIterator copy_b(_InputIterator __first, _InputIterator __last,
                                      _OutputIterator __result)
        {
            return _OutputIterator(tinystl::__copy_backward_aux(__first.base(), __last.base(),
                                                                __result.base()));
        }
    };


    /**
     *  @brief 拷贝区间[first, last)的内容到result
     *  @param  first 输入迭代器
     *  @param  last 输入迭代器
     *  @param  result 输出迭代器
     *  @return result - (last - first)
     */
    template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator copy_backward(_InputIterator __first, _InputIterator __last,
                                         _OutputIterator __result)
    {
        const bool __in  = __is_normal_iterator<_InputIterator>::__value;
        const bool __out = __is_normal_iterator<_OutputIterator>::__value;
        return tinystl::__copy_backward_normal<__in, __out>::copy_b(__first, __last, __result);
    }


    /**
     *  @brief 区间[first, last)填充value值
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @param  value  任意类型
     *  @return 无
     */
    template<bool>
    struct __fill
    {
        template<typename _ForwardIterator, typename _Tp>
        static void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
        {
            while (__first != __last)
            {
                *__first = __value;
                ++__first;
            }
        }
    };



    /**
     *  @brief 区间[first, last)填充value值
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @param  value  任意类型
     *  @return 无
     *
     *  此版本value是scalar，拷贝到tmp更容易被编译器优化。
     */
    template<>
    struct __fill<true>
    {
        template<typename _ForwardIterator, typename _Tp>
        static void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
        {
            const _Tp __tmp = __value;
            while (__first != __last)
            {
                *__first = __tmp;
                ++__first;
            }
        }
    };


    /**
     *  @brief 区间[first, last)填充value值
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @param  value  任意类型
     *  @return 无
     */
    template<typename _ForwardIterator, typename _Tp>
    void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
    {
        const bool __scalar = ____is_scalar<_Tp>::__value;
        tinystl::__fill<__scalar>::fill(__first, __last, __value);
    }


    /**
     *  @brief 区间[first, last)填充value值
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @param  value  填充的值
     *  @return 无
     */
    inline void fill(unsigned char* __first, unsigned char* __last, const unsigned char& __c)
    {
        const unsigned char __tmp = __c;
        tinystl::memset(__first, __tmp, __last - __first);
    }


    /**
     *  @brief 区间[first, last)填充value值
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @param  value  填充的值
     *  @return 无
     */
    inline void fill(signed char* __first, signed char* __last, const signed char& __c)
    {
        const signed char __tmp = __c;
        tinystl::memset(__first, static_cast<signed char>(__tmp), __last - __first);
    }


    /**
     *  @brief 区间[first, last)填充value值
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @param  value  填充的值
     *  @return 无
     */
    inline void fill(char* __first, char* __last, const char& __c)
    {
        const char __tmp = __c;
        tinystl::memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
    }


    /**
     *  @brief [first, first + n)填充value值
     *  @param  first  区间开始
     *  @param  n      数量
     *  @param  value  填充的值
     *  @return first + n
     */
    template<bool>
    struct __fill_n
    {
        template<typename _OutputIterator, typename _Size, typename _Tp>
        static _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp& __value)
        {
            while (__n > 0)
            {
                *__first = __value;
                ++__first;
                --__n;
            }
            return __first;
        }
    };


    /**
     *  @brief [first, first + n)填充value值
     *  @param  first  区间开始
     *  @param  n      数量
     *  @param  value  填充的值
     *  @return first + n
     *
     *  此版本value是scalar，拷贝到tmp更容易被编译器优化。
     */
    template<>
    struct __fill_n<true>
    {
        template<typename _OutputIterator, typename _Size, typename _Tp>
        static _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp& __value)
        {
            const _Tp __tmp = __value;
            while (__n > 0)
            {
                *__first = __tmp;
                ++__first;
                --__n;
            }
            return __first;
        }
    };


    /**
     *  @brief [first, first + n)填充value值
     *  @param  first  区间开始
     *  @param  n      数量
     *  @param  value  填充的值
     *  @return first + n
     */
    template<typename _OutputIterator, typename _Size, typename _Tp>
    _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
        const bool __scalar = ____is_scalar<_Tp>::__value;
        return tinystl::__fill_n<__scalar>::fill_n(__first, __n, __value);
    }


    /**
     *  @brief [first, first + n)填充c值
     *  @param  first  区间开始
     *  @param  n      数量
     *  @param  c      填充的值
     *  @return first + n
     */
    template<typename _Size>
    inline unsigned char* fill_n(unsigned char* __first, _Size __n, const unsigned char& __c)
    {
        unsigned char* __last = __first + __n;
        tinystl::fill(__first, __last, __c);
        return __last;
    }


    /**
     *  @brief [first, first + n)填充c值
     *  @param  first  区间开始
     *  @param  n      数量
     *  @param  c      填充的值
     *  @return first + n
     */
    template<typename _Size>
    inline signed char* fill_n(signed char* __first, _Size __n, const signed char& __c)
    {
        signed char* __last = __first + __n;
        tinystl::fill(__first, __last, __c);
        return __last;
    }


    /**
     *  @brief [first, first + n)填充c值
     *  @param  first  区间开始
     *  @param  n      数量
     *  @param  c      填充的值
     *  @return first + n
     */
    template<typename _Size>
    inline char* fill_n(char* __first, _Size __n, const signed char& __c)
    {
        char* __last = __first + __n;
        tinystl::fill(__first, __last, __c);
        return __last;
    }


    template<typename _InputIterator1, typename _InputIterator2, typename _BinaryPredicate>
    pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
                                                    _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
        while (__first1 != __last1 && __binary_pred(*__first1, *__first2))
        {
            ++__first1;
            ++__first2;
        }
        return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }


    template<typename _InputIterator1, typename _InputIterator2>
    inline bool equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
    {
        while (__first1 != __last1)
        {
            if (!(*__first1 == *__first2))
            {
                return false;
            }
            ++__first1;
            ++__first2;
        }
        return true;
    }


    template<typename _InputIterator1, typename _InputIterator2, typename _BinaryPredicate>
    inline bool equal(_InputIterator1 __first1, _InputIterator1 __last1,
                      _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
        while (__first1 != __last1)
        {
            if (!__binary_pred(*__first1, *__first2))
            {
                return false;
            }
            ++__first1;
            ++__first2;
        }
        return true;
    }


    template<typename _InputIterator1, typename _InputIterator2, typename _Compare>
    bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                                 _InputIterator2 __first2, _InputIterator2 __last2,
                                 _Compare __comp)
    {
        while (__first1 != __last1 && __first2 != __last2)
        {
            if (__comp(*__first1, *__first2))
            {
                return true;
            }
            if (__comp(*__first2, *__first1))
            {
                return false;
            }
            ++__first1;
            ++__first2;
        }
        return __first1 == __last1 && __first2 != __last2;
    }


    inline bool lexicographical_compare(const unsigned char* __first1, const unsigned char* __last1,
                                        const unsigned char* __first2, const unsigned char* __last2)
    {
        const size_t __len1 = __last1 - __first1;
        const size_t __len2 = __last2 - __first2;
        const int __n = tinystl::memcmp(__first1, __first2, tinystl::min(__len1, __len2));
        return __n != 0 ? __n < 0 : __len1 < __len2;
    }

}


#endif
