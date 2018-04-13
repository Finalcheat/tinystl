#ifndef _TINYSTL_ARRAY_HPP_
#define _TINYSTL_ARRAY_HPP_

#include "stddef.hpp"
#include "iterator.hpp"


namespace tinystl {

    template<typename _Tp, tinystl::size_t _N>
    class array
    {
    public:
        typedef _Tp                                        value_type;
        typedef tinystl::size_t                            size_type;
        typedef tinystl::ptrdiff_t                         difference_type;
        typedef value_type&                                reference;
        typedef const value_type&                          const_reference;
        typedef value_type*                                pointer;
        typedef const value_type*                          const_pointer;
        typedef tinystl::__normal_iterator<pointer>        iterator;
        typedef tinystl::__normal_iterator<const_pointer>  const_iterator;
        typedef __reverse_iterator<iterator>               reverse_iterator;
        typedef __reverse_iterator<const_iterator>         const_reverse_iterator;

    public:
        value_type _elems[_N > 0 ? _N : 1];

    public:
        reference at(size_type __n)
        {
            return _elems[__n];
        }

        const_reference at(size_type __n) const
        {
            return _elems[__n];
        }

        reference operator[](size_type __n)
        {
            return _elems[__n];
        }

        const_reference operator[](size_type __n) const
        {
            return _elems[__n];
        }

        reference front()
        {
            return _elems[0];
        }

        const_reference front() const
        {
            return _elems[0];
        }

        reference back()
        {
            return _elems[size() - 1];
        }

        const_reference back() const
        {
            return _elems[size() - 1];
        }

        pointer data()
        {
            return pointer(_elems);
        }

        const_pointer data() const
        {
            return const_pointer(_elems);
        }

        iterator begin()
        {
            return iterator(_elems);
        }

        const_iterator begin() const
        {
            return const_iterator(_elems);
        }

        iterator end()
        {
            return iterator(_elems + size());
        }

        const_iterator end() const
        {
            return const_iterator(_elems + size());
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        bool empty() const
        {
            return (_N == 0);
        }

        size_type size() const
        {
            return _N;
        }

        size_type max_size() const
        {
            return size_t(-1) / sizeof(value_type);
        }

        void fill(const value_type& __v)
        {
            tinystl::fill_n(begin(), size(), __v);
        }

        void swap(array& __o)
        {
            for (size_t i = 0; i < size(); ++i)
            {
                tinystl::swap(_elems[i], __o[i]);
            }
        }
    };


    template<typename _Tp, size_t _N>
    inline bool operator==(const array<_Tp, _N>& __l, const array<_Tp, _N>& __r)
    {
        return tinystl::equal(__l.begin(), __l.end(), __r.begin());
    }


    template<typename _Tp, size_t _N>
    inline bool operator!=(const array<_Tp, _N>& __l, const array<_Tp, _N>& __r)
    {
        return !(__l == __r);
    }

}


#endif
