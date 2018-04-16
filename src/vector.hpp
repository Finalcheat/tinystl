#ifndef _TINYSTL_VECTOR_HPP_
#define _TINYSTL_VECTOR_HPP_ 1

#include "new_allocator.hpp"
#include "iterator.hpp"
#include "uninitialized.hpp"
#include "construct.hpp"
#include "iterator_base_funcs.hpp"
#include "algobase.hpp"


namespace tinystl {

    template<typename _Tp, typename _Alloc = tinystl::new_allocator<_Tp> >
    class vector
    {
    public:
        typedef _Tp                                        value_type;
        typedef tinystl::size_t                            size_type;
        typedef _Tp*                                       pointer;
        typedef const _Tp*                                 const_pointer;
        typedef tinystl::__normal_iterator<pointer>        iterator;
        typedef tinystl::__normal_iterator<const_pointer>  const_iterator;
        typedef __reverse_iterator<iterator>               reverse_iterator;
        typedef __reverse_iterator<const_iterator>         const_reverse_iterator;
        typedef _Tp&                                       reference;
        typedef const _Tp&                                 const_reference;
        typedef _Alloc                                     allocator_type;

    protected:
        typedef typename _Alloc::template rebind<_Tp>::other _Tp_alloc_type;
        struct _vector_impl : public _Tp_alloc_type
        {
            _Tp* _start;
            _Tp* _finish;
            _Tp* _end_of_storage;
            _vector_impl(const _Tp_alloc_type& __a) : _Tp_alloc_type(__a), _start(0), _finish(0),
                                                      _end_of_storage(0) { }
        };

        _Tp_alloc_type& _get_Tp_alloc()
        {
            return *static_cast<_Tp_alloc_type*>(&this->_impl);
        }

        const _Tp_alloc_type& _get_Tp_alloc() const
        {
            return *static_cast<const _Tp_alloc_type*>(&this->_impl);
        }

    public:
        explicit vector(const allocator_type& __a = allocator_type()) : _impl(__a) { }

        explicit vector(size_type __n, const value_type& __value = value_type(),
                        const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            if (__n)
            {
                this->_impl._start = this->_impl.allocate(__n);
                tinystl::__uninitialized_fill_n_a(this->_impl._start, __n, __value, __a);
                this->_impl._finish = this->_impl._start + __n;
                this->_impl._end_of_storage = this->_impl._finish;
            }
        }

        vector(const vector& __x) : _impl(__x._get_Tp_alloc())
        {
            const size_type __n = __x.size();
            if (__n)
            {
                this->_impl._start = this->_impl.allocate(__n);
                tinystl::__uninitialized_copy_a(__x.begin(), __x.end(), this->_impl._start, _get_Tp_alloc());
                this->_impl._finish = this->_impl._start + __n;
                this->_impl._end_of_storage = this->_impl._finish;
            }
        }

        vector& operator=(const vector& __v)
        {
            iterator __cur(__v._impl._start);
            if (__v.size() > this->size())
            {
                tinystl::copy(__cur, __cur + size(), begin());
                __cur += size();
                while (__cur != __v.end())
                {
                    push_back(*__cur);
                    ++__cur;
                }
            }
            else
            {
                tinystl::copy(__cur, __cur + __v.size(), begin());
                tinystl::_Destroy(begin() + __v.size(), end(), _get_Tp_alloc());
                this->_impl._finish = this->_impl._start + __v.size();
            }
            return *this;
        }

        template<typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last,
               const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            _initialize_dispatch(__first, __last, _Type());
        }

        ~vector()
        {
            tinystl::_Destroy(this->_impl._start, this->_impl._finish, _get_Tp_alloc());
            _impl.deallocate(this->_impl._start, capacity());
        }

    public:
        iterator begin()
        {
            return iterator(_impl._start);
        }

        const_iterator begin() const
        {
            return const_iterator(_impl._start);
        }

        iterator end()
        {
            return iterator(_impl._finish);
        }

        const_iterator end() const
        {
            return const_iterator(_impl._finish);
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

    public:
        size_type size() const
        {
            return _impl._finish - _impl._start;
        }

        size_type max_size() const
        {
            return _impl.max_size();
        }

        void resize(size_type __new_size, const value_type __x = value_type())
        {
        }

        size_type capacity() const
        {
            return _impl._end_of_storage - _impl._start;
        }

        bool empty() const
        {
            return _impl._start == _impl._finish;
        }

        void reserve(size_type __n)
        {
            if (capacity() < __n)
            {
                const size_type __old_size = size();
                pointer __cur = _impl.allocate(__n);
                tinystl::__uninitialized_copy_a(begin(), end(), __cur, _get_Tp_alloc());
                tinystl::_Destroy(this->_impl._start, this->_impl._finish, _get_Tp_alloc());
                _impl.deallocate(this->_impl._start, capacity());
                this->_impl._start = __cur;
                this->_impl._finish = __cur + __old_size;
                this->_impl._end_of_storage = __cur + __n;
            }
        }

    public:
        reference operator[](const size_type __index)
        {
            return *(_impl._start + __index);
        }

        const_reference operator[](const size_type __index) const
        {
            return *(_impl._start + __index);
        }

        reference at(const size_type __index)
        {
            return *(_impl._start + __index);
        }

        const_reference at(const size_type __index) const
        {
            return *(_impl._start + __index);
        }

        reference front()
        {
            return *begin();
        }

        const_reference front() const
        {
            return *begin();
        }

        reference back()
        {
            return *(end() - 1);
        }

        const_reference back() const
        {
            return *(end() - 1);
        }

        pointer data()
        {
            return pointer(_impl._start);
        }

        const_pointer data() const
        {
            return const_pointer(_impl._start);
        }

    public:
        void assign(size_type __n, const value_type& __x)
        {
            _fill_assign(__n, __x);
        }

        template<typename _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            _assign_dispatch(__first, __last, _Type());
        }

        void push_back(const value_type& __x)
        {
            if (_impl._finish != _impl._end_of_storage)
            {
                // 还有剩余空间，直接构造
                _impl.construct(_impl._finish, __x);
                ++_impl._finish;
            }
            else
            {
                // 没有剩余空间，申请新的空间长度为原空间长度的2倍，拷贝原空间元素到新空间，最后释放原空间内存
                size_type __old_size = size();
                const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
                pointer __new_start = _impl.allocate(__len);
                pointer __new_finish = __new_start;
                __new_finish = tinystl::__uninitialized_copy_a(_impl._start, _impl._finish, __new_start,
                                                               allocator_type());
                _impl.construct(__new_finish, __x);
                ++__new_finish;
                tinystl::_Destroy(_impl._start, _impl._finish);
                _impl.deallocate(_impl._start, __old_size);
                _impl._start = __new_start;
                _impl._finish = __new_finish;
                _impl._end_of_storage = __new_start + __len;
            }
        }

        void pop_back()
        {
            --this->_impl._finish;
            this->_impl.destroy(this->_impl._finish);
        }

        iterator insert(iterator __position, const value_type& __x)
        {
            const size_type __n = tinystl::distance(begin(), __position);
            if (this->_impl._finish != this->_impl._end_of_storage && __position == end())
            {
                // 还有剩余空间并且是在end()前插入，相当于push_back()，直接构造元素即可
                this->_impl.construct(this->_impl._finish, __x);
                ++this->_impl._finish;
            }
            else
            {
                _insert_aux(__position, __x);
            }

            return (begin() + __n);
        }

        void insert(iterator __position, size_type __n, const value_type& __x)
        {
            _fill_insert(__position, __n, __x);
        }

        template<typename _InputIterator>
        void insert(iterator __position, _InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            _insert_dispatch(__position, __first, __last, _Type());
        }

        iterator erase(iterator __position)
        {
            iterator __next = __position + 1;
            if (__next != end())
            {
                tinystl::copy(__next, end(), __position);
            }
            --this->_impl._finish;
            this->_impl.destroy(this->_impl._finish);
            return __position;
        }

        template<typename _InputIterator>
        iterator erase(_InputIterator __first, _InputIterator __last)
        {
            while (__first != __last)
            {
                --__last;
                erase(__last);
            }
            return __first;
        }

        void swap(vector& __v)
        {
            tinystl::swap(this->_impl._start, __v._impl._start);
            tinystl::swap(this->_impl._finish, __v._impl._finish);
            tinystl::swap(this->_impl._end_of_storage, __v._impl._end_of_storage);
        }

        void clear()
        {
            tinystl::_Destroy(begin(), end(), _get_Tp_alloc());
            this->_impl._finish = this->_impl._start;
        }

    private:
        template<typename _Integer>
        void _initialize_dispatch(_Integer __n, _Integer __value, __true_type)
        {
            if (__n)
            {
                this->_impl._start = this->_impl.allocate(__n);
                tinystl::__uninitialized_fill_n_a(this->_impl._start, __n, __value, _get_Tp_alloc());
                this->_impl._finish = this->_impl._start + __n;
                this->_impl._end_of_storage = this->_impl._finish;
            }
        }

        template<typename _InputIterator>
        void _initialize_dispatch(_InputIterator __first, _InputIterator __last, __false_type)
        {
            typedef typename tinystl::iterator_traits<_InputIterator>::iterator_category _Category;
            _range_initialize(__first, __last, _Category());
        }

        template<typename _InputIterator>
        void _range_initialize(_InputIterator __first, _InputIterator __last, input_iterator_tag)
        {
            while (__first != __last)
            {
                push_back(*__first);
                ++__first;
            }
        }

        template<typename _ForwardIterator>
        void _range_initialize(_ForwardIterator __first, _ForwardIterator __last, forward_iterator_tag)
        {
            const size_type __n = tinystl::distance(__first, __last);
            this->_impl._start = this->_impl.allocate(__n);
            this->_impl._end_of_storage = this->_impl._start + __n;
            this->_impl._finish = tinystl::__uninitialized_copy_a(__first, __last, this->_impl._start,
                                                                  _get_Tp_alloc());
        }

        void _fill_insert(iterator __position, size_type __n, const value_type& __x)
        {
            const value_type __x_copy = __x;
            iterator __cur = __position;
            for (size_type i = 0; i < __n; ++i)
            {
                __position = insert(__position, __x_copy);
            }
        }

        template<typename _Integer>
        void _insert_dispatch(iterator __position, _Integer __n, _Integer __x, __true_type)
        {
            _fill_insert(__position, __n, __x);
        }

        template<typename _InputIterator>
        void _insert_dispatch(iterator __position, _InputIterator __first, _InputIterator __last,
                              __false_type)
        {
            for (; __first != __last; ++__first)
            {
                __position = ++insert(__position, *__first);
            }
        }

        void _insert_aux(iterator __position, const value_type& __x)
        {
            if (this->_impl._finish != this->_impl._end_of_storage)
            {
                // 还有剩余空间
                // 将[__position, end())的内容拷贝到[__position + 1, end() + 1)中
                // 首先在end()构造元素，因为end()之前未使用，必须对它特殊化处理，其他调用copy即可
                this->_impl.construct(this->_impl._finish, *(end() - 1));
                ++this->_impl._finish;
                const value_type __x_copy = __x;
                tinystl::copy_backward(__position, end() - 2, end() - 1);
                *__position = __x_copy;
            }
            else
            {
                // 空间不足，分配新空间为原空间2倍
                const size_type __old_size = size();
                const size_type __new_len = __old_size != 0 ? 2 * __old_size : 1;

                pointer __new_start(this->_impl.allocate(__new_len));
                pointer __new_finish(__new_start);
                __new_finish = tinystl::__uninitialized_copy_a(begin(), __position, __new_start,
                                                               _get_Tp_alloc());
                this->_impl.construct(__new_finish, __x);
                ++__new_finish;
                __new_finish = tinystl::__uninitialized_copy_a(__position, end(), __new_finish,
                                                               _get_Tp_alloc());

                // 释放旧空间
                tinystl::_Destroy(begin(), end(), _get_Tp_alloc());
                this->_impl.deallocate(this->_impl._start, capacity());

                this->_impl._start = __new_start;
                this->_impl._finish = __new_finish;
                this->_impl._end_of_storage = __new_start + __new_len;
            }
        }

        void _fill_assign(size_type __n, const value_type& __x)
        {
            const value_type __x_copy = __x;
            if (__n >= size())
            {
                tinystl::fill_n(this->_impl._start, size(), __x_copy);
                __n -= size();
                insert(end(), __n, __x);
            }
            else
            {
                tinystl::fill_n(this->_impl._start, __n, __x_copy);
            }
        }

        template<typename _Integer>
        void _assign_dispatch(_Integer __n, _Integer __x, __true_type)
        {
            _fill_assign(__n, __x);
        }

        template<typename _InputIterator>
        void _assign_dispatch(_InputIterator __first, _InputIterator __last, __false_type)
        {
            iterator __cur = begin();
            while (__cur != end() && __first != __last)
            {
                *__cur = *__first;
                ++__cur;
                ++__first;
            }
            if (__first != __last)
            {
                insert(end(), __first, __last);
            }
        }

    private:
        _vector_impl _impl;

    };


    template<typename _Tp, typename _Alloc>
    inline bool operator==(const vector<_Tp, _Alloc>& __l, const vector<_Tp, _Alloc>& __r)
    {
        if (__l.size() != __r.size())
        {
            return false;
        }
        return tinystl::equal(__l.begin(), __l.end(), __r.begin());
    }


    template<typename _Tp, typename _Alloc>
    inline bool operator!=(const vector<_Tp, _Alloc>& __l, const vector<_Tp, _Alloc>& __r)
    {
        return !(__l == __r);
    }

}

#endif
