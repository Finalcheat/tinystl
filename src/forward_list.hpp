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
        /**
         *  @brief  重载*操作符，返回节点值
         *  @return 对应节点的值
         */
        reference operator*() const
        {
            return _node->_value;
        }

        /**
         *  @brief  重载->操作符，返回指向节点值的指针
         *  @return 指向对应节点值的指针
         */
        pointer operator->() const
        {
            return &(_node->_value);
        }

        /**
         *  @brief  重载++操作符，节点往前走一步，返回自身
         *  @return *this
         */
        _Self& operator++()
        {
            _node = _node->_next;
            return *this;
        }

        /**
         *  @brief  重载++操作符，节点往前走一步，返回旧值
         *  @return 旧值
         */
        _Self operator++(int)
        {
            __forward_list_node<_Tp> __tmp = *_node;
            _node = _node->_next;
            return __tmp;
        }

        /**
         *  @brief  重载==操作符，判断两迭代器是否相等
         *  @return true/false
         */
        bool operator==(const _Self& __f) const
        {
            return _node == __f._node;
        }

        /**
         *  @brief  重载!=操作符，判断两迭代器是否不相等
         *  @return true/false
         */
        bool operator!=(const _Self& __f) const
        {
            return _node != __f._node;
        }

        /**
         *  @brief  返回迭代器底部的node节点
         *  @return node节点
         */
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
        /**
         *  @brief  重载*操作符，返回节点值
         *  @return 对应节点的值
         */
        reference operator*() const
        {
            return _node->_value;
        }

        /**
         *  @brief  重载->操作符，返回指向节点值的指针
         *  @return 指向对应节点值的指针
         */
        pointer operator->() const
        {
            return &(_node->_value);
        }

        /**
         *  @brief  重载++操作符，节点往前走一步，返回自身
         *  @return *this
         */
        _Self& operator++()
        {
            _node = _node->_next;
            return *this;
        }

        /**
         *  @brief  重载++操作符，节点往前走一步，返回旧值
         *  @return 旧值
         */
        _Self operator++(int)
        {
            _Node* __tmp = _node;
            _node = _node->_next;
            return _Self(__tmp);
        }

        /**
         *  @brief  重载==操作符，判断两迭代器是否相等
         *  @return true/false
         */
        bool operator==(const _Self& __f) const
        {
            return _node == __f._node;
        }

        /**
         *  @brief  重载!=操作符，判断两迭代器是否不相等
         *  @return true/false
         */
        bool operator!=(const _Self& __f) const
        {
            return _node != __f._node;
        }

        /**
         *  @brief  返回迭代器底部的node节点
         *  @return node节点
         */
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

        /**
         *  @brief  返回Tp类型的内存分配器
         *  @return Tp类型内存分配器
         */
        _Tp_alloc_type _get_Tp_alloc() const
        {
            return _Tp_alloc_type(_get_Node_alloc());
        }

        /**
         *  @brief  返回Node节点类型的内存分配器
         *  @return Node节点类型内存分配器
         */
        _Node_alloc_type& _get_Node_alloc()
        {
            return *static_cast<_Node_alloc_type*>(&this->_impl);
        }

        /**
         *  @brief  返回Node节点类型的内存分配器
         *  @return Node节点类型内存分配器
         */
        const _Node_alloc_type& _get_Node_alloc() const
        {
            return *static_cast<const _Node_alloc_type*>(&this->_impl);
        }

    protected:
        typedef __forward_list_node<_Tp>  _Node;

        /**
         *  @brief  分配1个Node节点的内存空间
         *  @return 指向新分配的Node节点指针
         */
        _Node* _get_node()
        {
            return _impl._Node_alloc_type::allocate(1);
        }

        /**
         *  @brief  释放Node节点的内存空间
         *  @param  p    需要释放的Node节点指针
         *  @return 无
         */
        void _put_node(_Node* __p)
        {
            _impl._Node_alloc_type::deallocate(__p, 1);
        }

        /**
         *  @brief  根据v的值构造1个Node节点
         *  @param  n    需要构造的值
         *  @return 指向新构造的Node节点指针
         */
        _Node* _create_node(const value_type& __v)
        {
            _Node* __p = this->_get_node();
            _get_Tp_alloc().construct(&__p->_value, __v);
            return __p;
        }

        /**
         *  @brief  初始化头部（哨子）节点，内部用
         *  @return 无
         */
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
        /**
         *  @brief  返回头部（哨子）节点的迭代器
         *  @return 哨子节点迭代器
         */
        iterator before_begin()
        {
            return iterator(_impl._head);
        }

        /**
         *  @brief  返回头部（哨子）节点的迭代器
         *  @return 哨子节点迭代器
         */
        const_iterator before_begin() const
        {
            return const_iterator(_impl._head);
        }

        /**
         *  @brief  返回外部可用的首节点的迭代器
         *  @return 首节点迭代器
         */
        iterator begin()
        {
            return iterator((_impl._head)->_next);
        }

        /**
         *  @brief  返回外部可用的首节点的迭代器
         *  @return 首节点迭代器
         */
        const_iterator begin() const
        {
            return const_iterator((_impl._head)->_next);
        }

        /**
         *  @brief  返回尾节点的迭代器
         *  @return 尾节点迭代器
         */
        iterator end()
        {
            return iterator(0);
        }

        /**
         *  @brief  返回尾节点的迭代器
         *  @return 尾节点迭代器
         */
        const_iterator end() const
        {
            return const_iterator(0);
        }

    public:
        /**
         *  @brief  判断容器是否为空
         *  @return true/false
         */
        bool empty() const
        {
            return _impl._head->_next == 0;
        }

        /**
         *  @brief  返回容器节点的最大数量
         *  @return 节点最大数量
         */
        size_type max_size() const
        {
            return _get_Tp_alloc().max_size();
        }

    public:
        /**
         *  @brief  返回外部可用的首节点值
         *  @return 首节点值
         */
        reference front()
        {
            return _impl._head->_next->_value;
        }

        /**
         *  @brief  返回外部可用的首节点值
         *  @return 首节点值
         */
        const_reference front() const
        {
            return _impl._head->_next->_value;
        }

    public:
        /**
         *  @brief  填充n个v元素
         *  @param  n    数量
         *  @param  v    填充的元素
         *  @return 无
         */
        void assign(size_type __n, const value_type& __v)
        {
            _assign(__n, __v);
        }

        /**
         *  @brief  填充[first, last)的元素
         *  @param  first    区间开始
         *  @param  last     区间结束
         *  @return 无
         */
        template<typename _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            return _assign_dispatch(__first, __last, _Type());
        }

        /**
         *  @brief  往链表头部插入新元素v
         *  @param  v    元素
         *  @return 无
         */
        void push_front(const value_type& __v)
        {
            _Node* __p = _create_node(__v);
            __p->_next = (_impl._head)->_next;
            _impl._head->_next = __p;
        }

        /**
         *  @brief  移除链表头部元素
         *  @return 无
         */
        void pop_front()
        {
            _Node* __first = _impl._head->_next;
            _impl._head->_next = __first->_next;

            // destroy __first
            _get_Tp_alloc().destroy(&__first->_value);
            _put_node(__first);
        }

        /**
         *  @brief  position节点后插入新元素v
         *  @param  position    节点迭代器
         *  @param  v           元素
         *  @return 新元素的迭代器
         */
        iterator insert_after(const_iterator __position, const value_type& __v)
        {
            _Node* __p = _create_node(__v);
            _Node* __p_base = (_Node*)(__position.base());
            __p->_next = __p_base->_next;
            __p_base->_next = __p;

            return iterator(__p);
        }

        /**
         *  @brief  position节点后插入n个新元素v
         *  @param  position    节点迭代器
         *  @param  n           数量
         *  @param  v           元素
         *  @return position + n
         */
        iterator insert_after(const_iterator __position, size_type __n, const value_type& __v)
        {
            for (; __n > 0; --__n)
            {
                __position = insert_after(__position, __v);
            }
            return iterator((_Node*)(__position.base()));
        }

        /**
         *  @brief  position节点后插入[first, last)区间内的元素
         *  @param  position    节点迭代器
         *  @param  first       区间开始
         *  @param  last        区间结束
         *  @return position + (last - first)
         */
        template<typename _InputIterator>
        iterator insert_after(const_iterator __position, _InputIterator __first, _InputIterator __last)
        {
            typedef typename tinystl::__is_integer<_InputIterator>::__type _Type;
            return _insert_after_dispatch(__position, __first, __last, _Type());
        }

        /**
         *  @brief  删除position节点的下一个节点
         *  @param  position    节点迭代器
         *  @return position的下一个节点
         */
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

        /**
         *  @brief  删除(position, last)区间的节点
         *  @param  position    节点迭代器
         *  @param  last        区间结束
         *  @return last
         */
        iterator erase_after(const_iterator __position, const_iterator __last)
        {
            const_iterator __position_copy = __position;
            for (; __position != __last; ++__position)
            {
                erase_after(__position_copy);
            }
            return iterator((_Node*)(__last.base()));
        }

        /**
         *  @brief  与另一个容器f交换
         *  @param  f    容器
         *  @return 无
         */
        void swap(forward_list& __f)
        {
            tinystl::swap(before_begin().base()->_next, __f.before_begin().base()->_next);
        }

        /**
         *  @brief  调整容器的大小为n
         *  @param  n    大小
         *  @return 无
         */
        void resize(size_type __n)
        {
            resize(__n, value_type());
        }

        /**
         *  @brief  调整容器的大小为n，如果大于原有空间，插入；否则删除
         *  @param  n    大小
         *  @param  v    元素
         *  @return 无
         */
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

        /**
         *  @brief  清除容器中内容
         *  @return 无
         */
        void clear()
        {
            erase_after(before_begin(), end());
        }

    public:
        // void splice_after(const_iterator __position, forward_list& __f);

        // void splice_after(const_iterator __position, forward_list& __f, const_iterator __i);

        // void splice_after(const_iterator __position, forward_list& __f,
        //                   const_iterator __first, const_iterator __last);

        /**
         *  @brief  删除容器内所有元素为v的节点
         *  @param  v    元素
         *  @return 无
         */
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

        /**
         *  @brief  删除容器内所有pred(元素)==true的节点
         *  @param  pred    函数对象
         *  @return 无
         */
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

        /**
         *  @brief  相邻元素重复的节点变唯一
         *  @return 无
         */
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

        /**
         *  @brief  相邻元素符合条件的节点变唯一
         *  @param  p    函数对象
         *  @return 无
         */
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

        /**
         *  @brief  合并容器f的内容，当前容器内容和f的内容都是按字典序排序好的，合并后保持排序状态
         *  @param  f    容器
         *  @return 无
         */
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

        /**
         *  @brief  合并容器f的内容，当前容器内容和f的内容都是已排序，合并后保持排序状态
         *  @param  f       容器
         *  @param  comp    比较大小函数对象
         *  @return 无
         */
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

        /**
         *  @brief  反转单链表
         *  @return 无
         */
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
        /**
         *  @brief  insert_after分发之一
         *  @param  position    节点迭代器
         *  @param  n           数量
         *  @param  v           元素
         *  @return position + n
         */
        template<typename _Integer>
        iterator _insert_after_dispatch(const_iterator __position, _Integer __n, _Integer __v, __true_type)
        {
            for (; __n > 0; --__n)
            {
                __position = insert_after(__position, __v);
            }
            return iterator((_Node*)(__position.base()));
        }

        /**
         *  @brief  insert_after分发之一
         *  @param  position    节点迭代器
         *  @param  first       区间开始
         *  @param  last        区间结束
         *  @return position + (last - first)
         */
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

        /**
         *  @brief  填充n个v元素
         *  @param  n    数量
         *  @param  v    填充的元素
         *  @return 无
         */
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

        /**
         *  @brief  assign分发之一
         *  @param  n    数量
         *  @param  v    填充的元素
         *  @return 无
         */
        template<typename _Integer>
        void _assign_dispatch(_Integer __n, _Integer __v, __true_type)
        {
            _assign(__n, __v);
        }

        /**
         *  @brief  assign分发之一
         *  @param  first    区间开始
         *  @param  last     区间结束
         *  @return 无
         */
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
