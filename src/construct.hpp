#ifndef _TINYSTL_CONSTRUCT_HPP_
#define _TINYSTL_CONSTRUCT_HPP_ 1

#include "cpp_type_traits.hpp"


namespace tinystl {


    /**
     *  @brief  在指针p上构造内容value
     *  @param  p      指针
     *  @param  value  构造内容
     *  @return 无
     */
    template<typename _Tp1, typename _Tp2>
    inline void _Construct(_Tp1* __p, const _Tp2& __value)
    {
        ::new(static_cast<void*>(__p)) _Tp1(__value);
    }


    /**
     *  @brief  在指针p上构造内容
     *  @param  p      指针
     *  @return 无
     */
    template <typename _Tp>
    inline void _Construct(_Tp* __p)
    {
        ::new(static_cast<void*>(__p)) _Tp();
    }


    /**
     *  @brief  调用pointer指向的对象的析构函数
     *  @param  pointer      指针
     *  @return 无
     */
    template<typename _Tp>
    inline void _Destroy(_Tp* __pointer)
    {
        __pointer->~_Tp();
    }


    /**
     *  @brief  析构[first, last)区间
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @return 无
     *
     *  迭代器指向的类型不是POD类型，遍历区间调用析构函数
     */
    template<typename _ForwardIterator>
    inline void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
    {
        while (__first != __last)
        {
            tinystl::_Destroy(&*__first);
            ++__first;
        }
    }


    /**
     *  @brief  析构[first, last)区间
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @return 无
     *
     *  迭代器指向的类型是POD类型，无需做任何事情
     */
    template<typename _ForwardIterator>
    inline void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __true_type)
    {}


    /**
     *  @brief  析构[first, last)区间
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @return 无
     *
     *  判断是否是POD类型，转调上面两个函数之一
     */
    template<typename _ForwardIterator>
    inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
        typedef typename iterator_traits<_ForwardIterator>::value_type __value_type;
        typedef typename tinystl::____is_scalar<__value_type>::__type __type;
        tinystl::__destroy_aux(__first, __last, __type());
    }


    template<typename>
    class new_allocator;


    /**
     *  @brief  析构[first, last)区间
     *  @param  first  区间开始
     *  @param  last   区间结束
     *  @return 无
     */
    template<typename _ForwardIterator, typename _Tp>
    inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last, new_allocator<_Tp>)
    {
        _Destroy(__first, __last);
    }

}


#endif
