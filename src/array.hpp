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
        /**
         *  @brief  返回第n个位置的元素，如果n不在范围之内，抛出std::out_of_range异常
         *  @param  n  位置
         *  @return 对应位置的元素值
         */
        reference at(size_type __n)
        {
            return _elems[__n];
        }

        /**
         *  @brief  返回第n个位置的元素，如果n不在范围之内，抛出std::out_of_range异常
         *  @param  n  位置
         *  @return 对应位置的元素值
         */
        const_reference at(size_type __n) const
        {
            return _elems[__n];
        }

        /**
         *  @brief  返回第n个位置的元素，如果n不在范围之内，结果未定义
         *  @param  n  位置
         *  @return 对应位置的元素值
         */
        reference operator[](size_type __n)
        {
            return _elems[__n];
        }

        /**
         *  @brief  返回第n个位置的元素，如果n不在范围之内，结果未定义
         *  @param  n  位置
         *  @return 对应位置的元素值
         */
        const_reference operator[](size_type __n) const
        {
            return _elems[__n];
        }

        /**
         *  @brief  返回首元素值，若首元素不存在，结果未定义
         *  @return 首元素的值
         */
        reference front()
        {
            return _elems[0];
        }

        /**
         *  @brief  返回首元素值，若首元素不存在，结果未定义
         *  @return 首元素的值
         */
        const_reference front() const
        {
            return _elems[0];
        }

        /**
         *  @brief  返回尾元素值，若尾元素不存在，结果未定义
         *  @return 尾元素的值
         */
        reference back()
        {
            return _elems[size() - 1];
        }

        /**
         *  @brief  返回尾元素值，若尾元素不存在，结果未定义
         *  @return 尾元素的值
         */
        const_reference back() const
        {
            return _elems[size() - 1];
        }

        /**
         *  @brief  返回元素数据指针
         *  @return 数据指针
         */
        pointer data()
        {
            return pointer(_elems);
        }

        /**
         *  @brief  返回元素数据指针
         *  @return 数据指针
         */
        const_pointer data() const
        {
            return const_pointer(_elems);
        }

        /**
         *  @brief  返回首元素的迭代器
         *  @return 首元素迭代器
         */
        iterator begin()
        {
            return iterator(_elems);
        }

        /**
         *  @brief  返回首元素的迭代器
         *  @return 首元素迭代器
         */
        const_iterator begin() const
        {
            return const_iterator(_elems);
        }

        /**
         *  @brief  返回结尾迭代器
         *  @return 结尾迭代器
         */
        iterator end()
        {
            return iterator(_elems + size());
        }

        /**
         *  @brief  返回结尾迭代器
         *  @return 结尾迭代器
         */
        const_iterator end() const
        {
            return const_iterator(_elems + size());
        }

        /**
         *  @brief  返回尾元素反向迭代器
         *  @return 尾元素反向迭代器
         */
        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        /**
         *  @brief  返回尾元素反向迭代器
         *  @return 尾元素反向迭代器
         */
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        /**
         *  @brief  返回反向迭代器结尾
         *  @return 反向迭代器结尾
         */
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        /**
         *  @brief  返回反向迭代器结尾
         *  @return 反向迭代器结尾
         */
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        /**
         *  @brief  返回容器是否含有数据
         *  @return ture/false
         */
        bool empty() const
        {
            return (_N == 0);
        }

        /**
         *  @brief  返回容器元素数量
         *  @return 元素数量
         */
        size_type size() const
        {
            return _N;
        }

        /**
         *  @brief  返回容器内允许的最大元素数量
         *  @return 最大元素数量
         */
        size_type max_size() const
        {
            return size_t(-1) / sizeof(value_type);
        }

        /**
         *  @brief  将容器内所有元素值替换为v
         *  @param  v  填充值
         *  @return 无
         */
        void fill(const value_type& __v)
        {
            tinystl::fill_n(begin(), size(), __v);
        }

        /**
         *  @brief  交换两个容器内容
         *  @param  o  交换的容器
         *  @return 无
         */
        void swap(array& __o)
        {
            for (size_t i = 0; i < size(); ++i)
            {
                tinystl::swap(_elems[i], __o[i]);
            }
        }
    };


    /**
     *  @brief  重载==判断两个容器是否相等
     *  @param  l  容器1
     *  @param  r  容器2
     *  @return true（相等）/false（不相等）
     */
    template<typename _Tp, size_t _N>
    inline bool operator==(const array<_Tp, _N>& __l, const array<_Tp, _N>& __r)
    {
        return tinystl::equal(__l.begin(), __l.end(), __r.begin());
    }


    /**
     *  @brief  重载!=判断两个容器是否不相等
     *  @param  l  容器1
     *  @param  r  容器2
     *  @return true（不相等）/false（相等）
     */
    template<typename _Tp, size_t _N>
    inline bool operator!=(const array<_Tp, _N>& __l, const array<_Tp, _N>& __r)
    {
        return !(__l == __r);
    }

}


#endif
