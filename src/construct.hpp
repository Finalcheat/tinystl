#ifndef _TINYSTL_CONSTRUCT_HPP_
#define _TINYSTL_CONSTRUCT_HPP_ 1

#include "cpp_type_traits.hpp"


namespace tinystl {


    template<typename _Tp1, typename _Tp2>
    inline void _Construct(_Tp1* __p, const _Tp2& __value)
    {
        ::new(static_cast<void*>(__p)) _Tp1(__value);
    }

    template <typename _Tp>
    inline void _Construct(_Tp* __p)
    {
        ::new(static_cast<void*>(__p)) _Tp();
    }


    template<typename _Tp>
    inline void _Destroy(_Tp* __pointer)
    {
        __pointer->~_Tp();
    }


    template<typename _ForwardIterator>
    inline void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
    {
        while (__first != __last)
        {
            tinystl::_Destroy(&*__first);
            ++__first;
        }
    }


    template<typename _ForwardIterator>
    inline void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __true_type)
    {}


    template<typename _ForwardIterator>
    inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
        typedef typename iterator_traits<_ForwardIterator>::value_type __value_type;
        typedef typename tinystl::____is_scalar<__value_type>::__type __type;
        tinystl::__destroy_aux(__first, __last, __type());
    }


    template<typename>
    class new_allocator;


    template<typename _ForwardIterator, typename _Tp>
    inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last, new_allocator<_Tp>)
    {
        _Destroy(__first, __last);
    }

}


#endif
