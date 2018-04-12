#ifndef _TINYSTL_ITERATOR_BASE_FUNC_HPP_
#define _TINYSTL_ITERATOR_BASE_FUNC_HPP_ 1


#include "iterator_base_types.hpp"


namespace tinystl {

    template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type __distance(
        _InputIterator __first, _InputIterator __last, input_iterator_tag)
    {
        typename iterator_traits<_InputIterator>::difference_type __n = 0;
        while (__first != __last)
        {
            ++__n;
            ++__first;
        }
        return __n;
    }


    template<typename _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type __distance(
        _RandomAccessIterator __first, _RandomAccessIterator __last, random_access_iterator_tag)
    {
        return (__last - __first);
    }


    template<typename _Iterator>
    inline typename iterator_traits<_Iterator>::difference_type distance(
        _Iterator __first, _Iterator __last)
    {
        typedef typename iterator_traits<_Iterator>::iterator_category _Category;
        return tinystl::__distance(__first, __last, _Category());
    }

}


#endif
