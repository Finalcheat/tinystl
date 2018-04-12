#ifndef _TINYSTL_ITERATOR_HPP
#define _TINYSTL_ITERATOR_HPP 1

#include "iterator_base_types.hpp"


namespace tinystl {

    using tinystl::iterator_traits;
    using tinystl::iterator;

    template<typename _Iterator>
    class __normal_iterator
    {

    public:
        typedef typename iterator_traits<_Iterator>::iterator_category  iterator_category;
        typedef typename iterator_traits<_Iterator>::value_type         value_type;
        typedef typename iterator_traits<_Iterator>::difference_type    difference_type;
        typedef typename iterator_traits<_Iterator>::pointer            pointer;
        typedef typename iterator_traits<_Iterator>::reference          reference;

    protected:
        _Iterator _current;

    public:
        __normal_iterator() : _current(_Iterator()) {}

        explicit __normal_iterator(const _Iterator& __i) : _current(__i) {}

    public:
        const _Iterator& base() const
        {
            return _current;
        }

        reference operator*() const
        {
            return *_current;
        }

        pointer operator->() const
        {
            return _current;
        }

        __normal_iterator& operator++()
        {
            ++_current;
            return *this;
        }

        __normal_iterator& operator--()
        {
            --_current;
            return *this;
        }

        __normal_iterator operator++(int)
        {
            return __normal_iterator(_current++);
        }

        __normal_iterator operator--(int)
        {
            return __normal_iterator(_current--);
        }

        reference operator[](const difference_type& __n) const
        {
            return _current[__n];
        }

        __normal_iterator& operator+=(const difference_type& __n)
        {
            _current += __n;
            return *this;
        }

        __normal_iterator operator+(const difference_type& __n)
        {
            return __normal_iterator(_current + __n);
        }

        __normal_iterator& operator-=(const difference_type& __n)
        {
            _current -= __n;
            return *this;
        }

        __normal_iterator operator-(const difference_type& __n) const
        {
            return __normal_iterator(_current - __n);
        }

    };

    template<typename _Iterator>
    inline bool operator==(const __normal_iterator<_Iterator>& __lhs,
                           const __normal_iterator<_Iterator>& __rhs)
    {
        return __lhs.base() == __rhs.base();
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator==(const __normal_iterator<_IteratorL>& __lhs,
                           const __normal_iterator<_IteratorR>& __rhs)
    {
        return __lhs.base() == __rhs.base();
    }

    template<typename _Iterator>
    inline bool operator!=(const __normal_iterator<_Iterator>& __lhs,
                           const __normal_iterator<_Iterator>& __rhs)
    {
        return !(__lhs == __rhs);
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator!=(const __normal_iterator<_IteratorL>& __lhs,
                           const __normal_iterator<_IteratorR>& __rhs)
    {
        return !(__lhs == __rhs);
    }

    template<typename _Iterator>
    inline bool operator<(const __normal_iterator<_Iterator>& __lhs,
                          const __normal_iterator<_Iterator>& __rhs)
    {
        return __lhs.base() < __rhs.base();
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator<(const __normal_iterator<_IteratorL>& __lhs,
                          const __normal_iterator<_IteratorR>& __rhs)
    {
        return __lhs.base() < __rhs.base();
    }

    template<typename _Iterator>
    inline bool operator>(const __normal_iterator<_Iterator>& __lhs,
                          const __normal_iterator<_Iterator>& __rhs)
    {
        return __lhs.base() > __rhs.base();
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator>(const __normal_iterator<_IteratorL>& __lhs,
                          const __normal_iterator<_IteratorR>& __rhs)
    {
        return __lhs.base() > __rhs.base();
    }

    template<typename _Iterator>
    inline bool operator<=(const __normal_iterator<_Iterator>& __lhs,
                           const __normal_iterator<_Iterator>& __rhs)
    {
        return __lhs.base() <= __rhs.base();
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator<=(const __normal_iterator<_IteratorL>& __lhs,
                           const __normal_iterator<_IteratorR>& __rhs)
    {
        return __lhs.base() <= __rhs.base();
    }

    template<typename _Iterator>
    inline bool operator>=(const __normal_iterator<_Iterator>& __lhs,
                           const __normal_iterator<_Iterator>& __rhs)
    {
        return __lhs.base() >= __rhs.base();
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator>=(const __normal_iterator<_IteratorL>& __lhs,
                           const __normal_iterator<_IteratorR>& __rhs)
    {
        return __lhs.base() >= __rhs.base();
    }

    template<typename _Iterator>
    inline typename __normal_iterator<_Iterator>::difference_type
    operator-(const __normal_iterator<_Iterator>& __l, const __normal_iterator<_Iterator>& __r)
    {
        return __l.base() - __r.base();
    }


    template<typename _Iterator>
    class __reverse_iterator
    {
    protected:
        _Iterator _current;

    public:
        typedef _Iterator                                            iterator_type;
        typedef typename iterator_traits<_Iterator>::difference_type difference_type;
        typedef typename iterator_traits<_Iterator>::reference       reference;
        typedef typename iterator_traits<_Iterator>::pointer         pointer;

    public:
        __reverse_iterator() : _current() { }

        explicit __reverse_iterator(iterator_type __x) : _current(__x) { }

        __reverse_iterator(const __reverse_iterator& __x) : _current(__x._current) { }

        iterator_type base() const
        {
            return _current;
        }

        reference operator*() const
        {
            _Iterator __tmp = _current;
            return *--__tmp;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        __reverse_iterator& operator++()
        {
            --_current;
            return *this;
        }

        __reverse_iterator operator++(int)
        {
            __reverse_iterator __tmp = *this;
            --_current;
            return __tmp;
        }

        __reverse_iterator& operator--()
        {
            ++_current;
            return *this;
        }

        __reverse_iterator operator--(int)
        {
            __reverse_iterator __tmp = *this;
            ++_current;
            return __tmp;
        }

    };

    template<typename _Iterator>
    inline bool operator==(const __reverse_iterator<_Iterator>& __lhs,
                           const __reverse_iterator<_Iterator>& __rhs)
    {
        return __lhs.base() == __rhs.base();
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator==(const __reverse_iterator<_IteratorL>& __lhs,
                           const __reverse_iterator<_IteratorR>& __rhs)
    {
        return __lhs.base() == __rhs.base();
    }

    template<typename _Iterator>
    inline bool operator!=(const __reverse_iterator<_Iterator>& __lhs,
                           const __reverse_iterator<_Iterator>& __rhs)
    {
        return !(__lhs == __rhs);
    }

    template<typename _IteratorL, typename _IteratorR>
    inline bool operator!=(const __reverse_iterator<_IteratorL>& __lhs,
                           const __reverse_iterator<_IteratorR>& __rhs)
    {
        return !(__lhs == __rhs);
    }

}


#endif
