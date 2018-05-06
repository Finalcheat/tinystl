#ifndef _TINYSTL_FORWARD_LIST_HPP_
#define _TINYSTL_FORWARD_LIST_HPP_ 1


namespace tinystl {

    template<typename _Tp>
    struct __forward_list_node
    {
        typedef _Tp value_type;

        __forward_list_node(const value_type& __v) : _value(__v), _next(0) { }

        _Tp _value;
        __forward_list_node* _next;
    };


    template<typename _Tp>
    class __forward_list_iterator
    {
    public:
        typedef _Tp                            value_type;
        typedef value_type&                    reference;
        typedef value_type*                    pointer;
        typedef tinystl::ptrdiff_t             difference_type;
        typedef tinystl::forward_iterator_tag  iterator_category;
        typedef __forward_list_node<_Tp>       _Node;
        typedef __forward_list_iterator<_Tp>   _Self;

    public:
        __forward_list_iterator() : _node(0) { }

        explicit __forward_list_iterator(_Node* __f) : _node(__f) { }

        __forward_list_iterator(const _Self& __f) : _node(__f._node) { }

    public:
        reference operator*() const
        {
            return _node->_value;
        }

        pointer operator->() const
        {
            return &(_node->_value);
        }

        _Self& operator++()
        {
            _node = _node->_next;
            return *this;
        }

        _Self operator++(int)
        {
            __forward_list_node<_Tp> __tmp = *_node;
            _node = _node->_next;
            return __tmp;
        }

        bool operator==(const _Self& __f) const
        {
            return _node == __f._node;
        }

        bool operator!=(const _Self& __f) const
        {
            return _node != __f._node;
        }

        _Node* base() const
        {
            return _node;
        }

    private:
        _Node* _node;
    };


    template<typename _Tp>
    class __forward_list_const_iterator
    {
    public:
        typedef _Tp                                  value_type;
        typedef const value_type&                    reference;
        typedef const value_type*                    pointer;
        typedef tinystl::ptrdiff_t                   difference_type;
        typedef tinystl::forward_iterator_tag        iterator_category;
        typedef const __forward_list_node<_Tp>       _Node;
        typedef __forward_list_const_iterator<_Tp>   _Self;

    public:
        __forward_list_const_iterator() : _node(0) { }

        explicit __forward_list_const_iterator(_Node* __f) : _node(__f) { }

        __forward_list_const_iterator(const _Self& __f) : _node(__f._node) { }

        __forward_list_const_iterator(const __forward_list_iterator<_Tp>& __f) : _node(__f.base()) { }

    public:
        reference operator*() const
        {
            return _node->_value;
        }

        pointer operator->() const
        {
            return &(_node->_value);
        }

        _Self& operator++()
        {
            _node = _node->_next;
            return *this;
        }

        _Self operator++(int)
        {
            _Node* __tmp = _node;
            _node = _node->_next;
            return _Self(__tmp);
        }

        bool operator==(const _Self& __f) const
        {
            return _node == __f._node;
        }

        bool operator!=(const _Self& __f) const
        {
            return _node != __f._node;
        }

        const _Node* base() const
        {
            return _node;
        }

    private:
        const _Node* _node;
    };


    template<typename _Tp, typename _Alloc = tinystl::new_allocator<_Tp> >
    class forward_list
    {
    public:
        typedef _Tp                                 value_type;
        typedef _Alloc                              allocator_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type*                         pointer;
        typedef const pointer                       const_pointer;
        typedef tinystl::ptrdiff_t                  difference_type;
        typedef tinystl::size_t                     size_type;
        typedef __forward_list_iterator<_Tp>        iterator;
        typedef __forward_list_const_iterator<_Tp>  const_iterator;

    protected:
        typedef typename _Alloc::template rebind< __forward_list_node<_Tp> >::other _Node_alloc_type;
        typedef typename _Alloc::template rebind<_Tp>::other _Tp_alloc_type;
        struct _forward_list_impl : public _Node_alloc_type
        {
            __forward_list_node<_Tp>* _head;
            _forward_list_impl(const _Node_alloc_type& __a) : _Node_alloc_type(__a), _head(0) { }
        };

        _Tp_alloc_type _get_Tp_alloc() const
        {
            return _Tp_alloc_type(_get_Node_alloc());
        }

        _Node_alloc_type& _get_Node_alloc()
        {
            return *static_cast<_Node_alloc_type*>(&this->_impl);
        }

        const _Node_alloc_type& _get_Node_alloc() const
        {
            return *static_cast<const _Node_alloc_type*>(&this->_impl);
        }

    protected:
        typedef __forward_list_node<_Tp>  _Node;

        _Node* _get_node()
        {
            return _impl._Node_alloc_type::allocate(1);
        }

        void _put_node(_Node* __p)
        {
            _impl._Node_alloc_type::deallocate(__p, 1);
        }

        _Node* _create_node(const value_type& __v)
        {
            _Node* __p = this->_get_node();
            _get_Tp_alloc().construct(&__p->_value, __v);
            return __p;
        }

        void _init_head_node()
        {
            _Node* __p = this->_get_node();
            __p->_next = 0;
            _impl._head = __p;
        }

    public:
        explicit forward_list(const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            _init_head_node();
        }

        explicit forward_list(size_type __n, const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            _init_head_node();

            const value_type& __init = value_type();
            for (; __n > 0; --__n)
            {
                push_front(__init);
            }
        }

        explicit forward_list(size_type __n, const value_type& __v,
                              const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            _init_head_node();

            for (; __n > 0; --__n)
            {
                push_front(__v);
            }
        }

        template<typename _InputIterator>
        forward_list(_InputIterator __first, _InputIterator __last,
                     const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            _init_head_node();

            insert_after(this->before_begin(), __first, __last);
        }

        forward_list(const forward_list& __f) : _impl(__f._get_Tp_alloc())
        {
            _init_head_node();

            insert_after(this->before_begin(), __f.begin(), __f.end());
        }

        forward_list& operator=(const forward_list& __f)
        {
            clear();

            insert_after(this->before_begin(), __f.begin(), __f.end());

            return *this;
        }

        ~forward_list()
        {
            _Node* __p = _impl._head->_next;
            _put_node(_impl._head);
            while (__p)
            {
                _Node* __next = __p->_next;
                _get_Tp_alloc().destroy(&__p->_value);
                _put_node(__p);
                __p = __next;
            }
        }

    public:
        iterator before_begin()
        {
            return iterator(_impl._head);
        }

        const_iterator before_begin() const
        {
            return const_iterator(_impl._head);
        }

        iterator begin()
        {
            return iterator((_impl._head)->_next);
        }

        const_iterator begin() const
        {
            return const_iterator((_impl._head)->_next);
        }

        iterator end()
        {
            return iterator(0);
        }

        const_iterator end() const
        {
            return const_iterator(0);
        }

    public:
        bool empty() const
        {
            return _impl._head->_next == 0;
        }

        size_type max_size() const
        {
            return _get_Tp_alloc().max_size();
        }

    public:
        reference front()
        {
            return _impl._head->_next->_value;
        }

        const_reference front() const
        {
            return _impl._head->_next->_value;
        }

    public:
        void assign(size_type __n, const value_type& __v)
        {
            _assign(__n, __v);
        }

        template<typename _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            return _assign_dispatch(__first, __last, _Type());
        }

        void push_front(const value_type& __v)
        {
            _Node* __p = _create_node(__v);
            __p->_next = (_impl._head)->_next;
            _impl._head->_next = __p;
        }

        void pop_front()
        {
            _Node* __first = _impl._head->_next;
            _impl._head->_next = __first->_next;

            // destroy __first
            _get_Tp_alloc().destroy(&__first->_value);
            _put_node(__first);
        }

        iterator insert_after(const_iterator __position, const value_type& __v)
        {
            _Node* __p = _create_node(__v);
            _Node* __p_base = (_Node*)(__position.base());
            __p->_next = __p_base->_next;
            __p_base->_next = __p;

            return iterator(__p);
        }

        iterator insert_after(const_iterator __position, size_type __n, const value_type& __v)
        {
            for (; __n > 0; --__n)
            {
                __position = insert_after(__position, __v);
            }
            return iterator((_Node*)(__position.base()));
        }

        template<typename _InputIterator>
        iterator insert_after(const_iterator __position, _InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            return _insert_after_dispatch(__position, __first, __last, _Type());
        }

        iterator erase_after(const_iterator __position)
        {
            _Node* __p = (_Node*)(__position.base());
            _Node* __next = __p->_next;
            if (__next)
            {
                __p->_next = __next->_next;
                _get_Tp_alloc().destroy(&__next->_value);
                _put_node(__next);
            }
            return iterator(__p->_next);
        }

        iterator erase_after(const_iterator __position, const_iterator __last)
        {
            const_iterator __position_copy = __position;
            for (; __position != __last; ++__position)
            {
                erase_after(__position_copy);
            }
            return iterator((_Node*)(__last.base()));
        }

        void swap(forward_list& __f)
        {
            tinystl::swap(before_begin().base()->_next, __f.before_begin().base()->_next);
        }

        void resize(size_type __n)
        {
            resize(__n, value_type());
        }

        void resize(size_type __n, const value_type& __v)
        {
            iterator __prev = before_begin();
            for (iterator __cur = begin(); __n > 0 && __cur != end(); ++__cur, --__n)
            {
                __prev = __cur;
            }
            if (__n == 0)
            {
                erase_after(__prev, end());
            }
            else
            {
                insert_after(__prev, __n, __v);
            }
        }

        void clear()
        {
            erase_after(before_begin(), end());
        }

    public:
        // void splice_after(const_iterator __position, forward_list& __f);

        // void splice_after(const_iterator __position, forward_list& __f, const_iterator __i);

        // void splice_after(const_iterator __position, forward_list& __f,
        //                   const_iterator __first, const_iterator __last);

        void remove(const value_type& __v)
        {
            const value_type __v_copy = __v;
            const_iterator __prev = before_begin();
            const_iterator __cur = begin();
            while (__cur != end())
            {
                if (*__cur == __v_copy)
                {
                    __cur = erase_after(__prev);
                }
                else
                {
                    __prev = __cur;
                    ++__cur;
                }
            }
        }

        template<typename _Predicate>
        void remove_if(_Predicate __pred)
        {
            const_iterator __prev = before_begin();
            const_iterator __cur = begin();
            while (__cur != end())
            {
                if (__pred(*__cur))
                {
                    __cur = erase_after(__prev);
                }
                else
                {
                    __prev = __cur;
                    ++__cur;
                }
            }
        }

        void unique()
        {
            const_iterator __next = begin();
            while (__next != end())
            {
                const_iterator __prev = __next++;
                while (__next != end() && *__prev == *__next)
                {
                    __next = erase_after(__prev);
                }
            }
        }

        template<typename _BinaryPredicate>
        void unique(_BinaryPredicate __binary_pred)
        {
            const_iterator __next = begin();
            while (__next != end())
            {
                const_iterator __prev = __next++;
                while (__next != end() && __binary_pred(*__prev, *__next))
                {
                    __next = erase_after(__prev);
                }
            }
        }

        void merge(forward_list& __f)
        {
            const_iterator __prev = before_begin();
            const_iterator __first1 = begin();
            const_iterator __last1 = end();
            const_iterator __first2 = __f.begin();
            const_iterator __last2 = __f.end();
            while (__first1 != __last1 && __first2 != __last2)
            {
                if (*__first1 < *__first2)
                {
                    __prev = __first1;
                    ++__first1;
                }
                else
                {
                    __prev = insert_after(__prev, *__first2);
                    ++__first2;
                }
            }

            if (__first2 != __last2)
            {
                insert_after(__prev, __first2, __last2);
            }
        }

        template<typename _Compare>
        void merge(forward_list& __f, _Compare __comp)
        {
            const_iterator __prev = before_begin();
            const_iterator __first1 = begin();
            const_iterator __last1 = end();
            const_iterator __first2 = __f.begin();
            const_iterator __last2 = __f.end();
            while (__first1 != __last1 && __first2 != __last2)
            {
                if (__comp(*__first1, *__first2))
                {
                    __prev = __first1;
                    ++__first1;
                }
                else
                {
                    __prev = insert_after(__prev, *__first2);
                    ++__first2;
                }
            }

            if (__first2 != __last2)
            {
                insert_after(__prev, __first2, __last2);
            }
        }

        // void sort();

        // template<typename _Compare>
        // void sort(_Compare __comp);

        void reverse()
        {
            _Node* __p = begin().base();
            if (__p)
            {
                _Node* __next = __p->_next;
                __p->_next = 0;
                while (__next)
                {
                    _Node* __tmp = __next->_next;
                    __next->_next = __p;
                    __p = __next;
                    __next = __tmp;
                }
                this->_impl._head->_next = __p;
            }
        }

    protected:
        template<typename _Integer>
        iterator _insert_after_dispatch(const_iterator __position, _Integer __n, _Integer __v, __true_type)
        {
            for (; __n > 0; --__n)
            {
                __position = insert_after(__position, __v);
            }
            return iterator((_Node*)(__position.base()));
        }

        template<typename _InputIterator>
        iterator _insert_after_dispatch(const_iterator __position, _InputIterator __first,
                                        _InputIterator __last, __false_type)
        {
            for (; __first != __last; ++__first)
            {
                __position = insert_after(__position, *__first);
            }
            return iterator((_Node*)(__position.base()));
        }

        void _assign(size_type __n, const value_type& __v)
        {
            const value_type __v_copy = __v;
            iterator __cur = begin();
            for (; __n > 0 && __cur != end(); --__n)
            {
                *__cur = __v_copy;
                ++__cur;
            }
            if (__cur == end())
            {
                while (__n > 0)
                {
                    push_front(__v_copy);
                    --__n;
                }
            }
        }

        template<typename _Integer>
        void _assign_dispatch(_Integer __n, _Integer __v, __true_type)
        {
            _assign(__n, __v);
        }

        template<typename _InputIterator>
        void _assign_dispatch(_InputIterator __first, _InputIterator __last, __false_type)
        {
            iterator __prev = before_begin();
            for (iterator __cur = begin(); __first != __last && __cur != end(); ++__first, ++__cur)
            {
                *__cur = *__first;
                __prev = __cur;
            }
            if (__first != __last)
            {
                insert_after(__prev, __first, __last);
            }
        }

    private:
        _forward_list_impl _impl;
    };

}


#endif
