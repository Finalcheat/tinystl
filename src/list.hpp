#ifndef _TINYSTL_LIST_HPP_
#define _TINYSTL_LIST_HPP_ 1


namespace tinystl {

    template<typename _Tp>
    struct __list_node
    {
        typedef _Tp value_type;

        __list_node() : _value(value_type()), _next(0), _prev(0) { }

        __list_node(const value_type& __v) : _value(__v), _next(0), _prev(0) { }

        _Tp _value;
        __list_node* _next;
        __list_node* _prev;
    };

    template<typename _Tp>
    class __list_const_iterator;

    template<typename _Tp>
    class __list_iterator
    {
    public:
        typedef _Tp                                  value_type;
        typedef _Tp*                                 pointer;
        typedef _Tp&                                 reference;
        typedef tinystl::ptrdiff_t                   difference_type;
        typedef tinystl::bidirectional_iterator_tag  iterator_category;
        typedef __list_node<_Tp>                     _Node;
        typedef __list_iterator<_Tp>                 _Self;

    public:
        __list_iterator() : _node() { }

        explicit __list_iterator(_Node* __x) : _node(__x) { }

        __list_iterator(const _Self& __l) : _node(__l._node) { }

        __list_iterator(const __list_const_iterator<_Tp>& __l) : _node((_Node*)(__l.base())) { }

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
            _Self __tmp = *this;
            ++(*this);
            return __tmp;
        }

        _Self& operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        _Self operator--(int)
        {
            _Self __tmp = *this;
            --(*this);
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
    class __list_const_iterator
    {
    public:
        typedef _Tp                                  value_type;
        typedef const _Tp*                           pointer;
        typedef const _Tp&                           reference;
        typedef tinystl::ptrdiff_t                   difference_type;
        typedef tinystl::bidirectional_iterator_tag  iterator_category;
        typedef const __list_node<_Tp>               _Node;
        typedef __list_const_iterator<_Tp>           _Self;

    public:
        __list_const_iterator() : _node(0) { }

        explicit __list_const_iterator(_Node* __x) : _node(__x) { }

        __list_const_iterator(const _Self& __l) : _node(__l._node) { }

        __list_const_iterator(const __list_iterator<_Tp>& __l) : _node(__l.base()) { }

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
            _Self __tmp = *this;
            ++(*this);
            return __tmp;
        }

        _Self& operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        _Self operator--(int)
        {
            _Self __tmp = *this;
            --(*this);
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

        const _Node* base() const
        {
            return _node;
        }

    private:
        const _Node* _node;
    };


    template<typename _Tp, typename _Alloc = tinystl::new_allocator<_Tp> >
    class list
    {
    public:
        typedef _Tp                         value_type;
        typedef _Tp*                        pointer;
        typedef const _Tp*                  const_pointer;
        typedef value_type&                 reference;
        typedef const value_type&           const_reference;
        typedef tinystl::size_t             size_type;
        typedef tinystl::ptrdiff_t          difference_type;
        typedef __list_iterator<_Tp>        iterator;
        typedef __list_const_iterator<_Tp>  const_iterator;
        typedef _Alloc                      allocator_type;

    protected:
        typedef __list_node<_Tp>                                     _Node;
        typedef typename _Alloc::template rebind<value_type>::other  _Tp_alloc_type;
        typedef typename _Alloc::template rebind<_Node>::other       _Node_alloc_type;

        struct _list_impl : public _Node_alloc_type
        {
            _Node* _head;
            _list_impl(const _Node_alloc_type& __a) : _Node_alloc_type(__a), _head(0) { }
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
            __p->_next = __p;
            __p->_prev = __p;
            _impl._head = __p;
        }

    public:
        explicit list(const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            _init_head_node();
        }

        explicit list(size_type __n, const value_type& __v = value_type(),
                      const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            _init_head_node();
            for (; __n > 0; --__n)
            {
                push_front(__v);
            }
        }

        template<typename _InputIterator>
        list(_InputIterator __first, _InputIterator __last,
             const allocator_type& __a = allocator_type()) : _impl(__a)
        {
            _init_head_node();

            insert(end(), __first, __last);
        }

        list(const list& __l) : _impl(__l._get_Tp_alloc())
        {
            _init_head_node();

            insert(end(), __l.begin(), __l.end());
        }

        list& operator=(const list& __l)
        {
            clear();

            insert(end(), __l.begin(), __l.end());

            return *this;
        }

        ~list()
        {
            clear();
            _Node* __head = _impl._head;
            _put_node(__head);
        }

    public:
        iterator begin()
        {
            return iterator(this->_impl._head->_next);
        }

        const_iterator begin() const
        {
            return const_iterator(this->_impl._head->_next);
        }

        iterator end()
        {
            return iterator(this->_impl._head);
        }

        const_iterator end() const
        {
            return const_iterator(this->_impl._head);
        }

    public:
        bool empty() const
        {
            return begin() == end();
        }

        size_type size() const
        {
            return tinystl::distance(begin(), end());
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

        reference back()
        {
            return _impl._head->_prev->_value;
        }

        const_reference back() const
        {
            return _impl._head->_prev->_value;
        }

    public:
        void assign(size_type __n, const value_type& __v)
        {
            _assign_aux(__n, __v);
        }

        template<typename _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            _assign_dispatch(__first, __last, _Type());
        }

        void push_front(const value_type& __v)
        {
            _Node* __p = _create_node(__v);
            __p->_next = _impl._head->_next;
            __p->_prev = _impl._head;
            _impl._head->_next->_prev = __p;
            _impl._head->_next = __p;
        }

        void pop_front()
        {
            _Node* __first = _impl._head->_next;
            _impl._head->_next = __first->_next;
            __first->_next->_prev = _impl._head;

            // destroy __first
            _get_Tp_alloc().destroy(&__first->_value);
            _put_node(__first);
        }

        void push_back(const value_type& __v)
        {
            _Node* __p = _create_node(__v);
            _Node* __last = _impl._head->_prev;
            __p->_next = _impl._head;
            __p->_prev = __last;
            __last->_next = __p;
            _impl._head->_prev = __p;
        }

        void pop_back()
        {
            _Node* __last = _impl._head->_prev;
            __last->_prev->_next = __last->_next;
            _impl._head->_prev = __last->_prev;

            // destroy __last
            _get_Tp_alloc().destroy(&__last->_value);
            _put_node(__last);
        }

        iterator insert(iterator __position, const value_type& __v)
        {
            _Node* __p = _create_node(__v);
            _Node* __p_base = __position.base();
            __p->_next = __p_base;
            __p->_prev = __p_base->_prev;
            __p_base->_prev->_next = __p;
            __p_base->_prev = __p;
            return iterator(__p);
        }

        void insert(iterator __position, size_type __n, const value_type& __v)
        {
            _insert_aux(__position, __n, __v);
        }

        template<typename _InputIterator>
        void insert(iterator __position, _InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            _insert_dispatch(__position, __first, __last, _Type());
        }

        iterator erase(iterator __position)
        {
            _Node* __p = __position.base();
            _Node* __next = __p->_next;
            __p->_prev->_next = __next;
            if (__next)
            {
                __next->_prev = __p->_prev;
            }
            _get_Tp_alloc().destroy(&__p->_value);
            _put_node(__p);
            return iterator(__next);
        }

        iterator erase(iterator __first, iterator __last)
        {
            while (__first != __last)
            {
                __first = erase(__first);
            }
            return __last;
        }

        void swap(list& __l)
        {
            tinystl::swap(_impl._head, __l._impl._head);
        }

        void resize(size_type __n, const value_type& __v = value_type())
        {
            iterator __cur = begin();
            for (; __n > 0 && __cur != end(); --__n)
            {
                ++__cur;
            }
            if (__n == 0)
            {
                erase(__cur, end());
            }
            else
            {
                insert(__cur, __n, __v);
            }
        }

        void clear()
        {
            erase(begin(), end());
        }

    public:
        // void splice(iterator __position, list& __l);

        // void splice(iterator __position, list& __l, iterator __i);

        // void splice(iterator __position, list& __l, iterator __first, iterator __last);

        void remove(const value_type& __v)
        {
            const value_type __v_copy = __v;
            for (iterator __cur = begin(); __cur != end(); )
            {
                if (*__cur == __v_copy)
                {
                    __cur = erase(__cur);
                }
                else
                {
                    ++__cur;
                }
            }
        }

        template<typename _Predicate>
        void remove_if(_Predicate __pred)
        {
            for (iterator __cur = begin(); __cur != end(); )
            {
                if (__pred(*__cur))
                {
                    __cur = erase(__cur);
                }
                else
                {
                    ++__cur;
                }
            }
        }

        void unique()
        {
            iterator __next = begin();
            while (__next != end())
            {
                iterator __cur = __next++;
                while (__next != end() && *__cur == *__next)
                {
                    __next = erase(__next);
                }
            }
        }

        template<typename _BinaryPredicate>
        void unique(_BinaryPredicate __binary_pred)
        {
            iterator __next = begin();
            while (__next != end())
            {
                iterator __cur = __next++;
                while (__next != end() && __binary_pred(*__cur, *__next))
                {
                    __next = erase(__next);
                }
            }
        }

        void merge(list& __l)
        {
            iterator __first1 = begin();
            iterator __last1 = end();
            iterator __first2 = __l.begin();
            iterator __last2 = __l.end();
            while (__first1 != __last1 && __first2 != __last2)
            {
                if (*__first1 < *__first2)
                {
                    ++__first1;
                }
                else
                {
                    insert(__first1, *__first2);
                    ++__first2;
                }
            }

            if (__first2 != __last2)
            {
                insert(end(), __first2, __last2);
            }
        }

        template<typename _Compare>
        void merge(list& __l, _Compare __comp)
        {
            iterator __first1 = begin();
            iterator __last1 = end();
            iterator __first2 = __l.begin();
            iterator __last2 = __l.end();
            while (__first1 != __last1 && __first2 != __last2)
            {
                if (__comp(*__first1, *__first2))
                {
                    ++__first1;
                }
                else
                {
                    insert(__first1, *__first2);
                    ++__first2;
                }
            }

            if (__first2 != __last2)
            {
                insert(end(), __first2, __last2);
            }
        }

        // void sort();

        // template<typename _Compare>
        // void sort(_Compare __comp);

        void reverse()
        {
            for (iterator __next = begin(); __next != end(); )
            {
                iterator __cur = __next++;
                _Node* __p_cur = __cur.base();
                __p_cur->_next = __p_cur->_prev;
                __p_cur->_prev = __next.base();
            }

            _Node* __head = _impl._head;
            _Node* __next = __head->_next;
            _Node* __prev = __head->_prev;
            __head->_next = __prev;
            __head->_prev = __next;
        }

    protected:
        void _insert_aux(iterator __position, size_type __n, const value_type& __v)
        {
            for (; __n > 0; --__n)
            {
                __position = insert(__position, __v);
            }
        }

        template<typename _Integer>
        void _insert_dispatch(iterator __position, _Integer __n, _Integer __x, __true_type)
        {
            _insert_aux(__position, __n, __x);
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

        void _assign_aux(size_type __n, const value_type& __v)
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
            _assign_aux(__n, __v);
        }

        template<typename _InputIterator>
        void _assign_dispatch(_InputIterator __first, _InputIterator __last, __false_type)
        {
            iterator __cur = begin();
            for (; __first != __last && __cur != end(); ++__first, ++__cur)
            {
                *__cur = *__first;
            }
            if (__first != __last)
            {
                insert(__cur, __first, __last);
            }
        }

    private:
        _list_impl _impl;
    };

}


#endif
