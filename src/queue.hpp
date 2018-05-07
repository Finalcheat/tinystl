#ifndef _TINYSTL_QUEUE_HPP_
#define _TINYSTL_QUEUE_HPP_ 1

#include "list.hpp"


namespace tinystl {

    template<typename _Tp, typename _Container = tinystl::list<_Tp> >
    class queue
    {
    public:
        typedef typename _Container::value_type       value_type;
        typedef typename _Container::reference        reference;
        typedef typename _Container::const_reference  const_reference;
        typedef typename _Container::size_type        size_type;
        typedef _Container                            container_type;

    public:
        template<typename _Tp1, typename _Container1>
        friend bool operator==(const queue<_Tp1, _Container1>&, const queue<_Tp1, _Container1>&);

    public:
        explicit queue(const _Container& __c = _Container()) : _c(__c) { }

    public:
        bool empty() const
        {
            return _c.empty();
        }

        size_type size() const
        {
            return _c.size();
        }

        value_type& front()
        {
            return _c.front();
        }

        const value_type& front() const
        {
            return _c.front();
        }

        value_type& back()
        {
            return _c.back();
        }

        const value_type& back() const
        {
            return _c.back();
        }

        void push(const value_type& __v)
        {
            _c.push_back(__v);
        }

        void pop()
        {
            _c.pop_front();
        }

    protected:
        _Container _c;
    };

    template<typename _Tp1, typename _Container1>
    bool operator==(const queue<_Tp1, _Container1>& __l, const queue<_Tp1, _Container1>& __r)
    {
        return __l._c == __r._c;
    }

    template<typename _Tp1, typename _Container1>
    bool operator!=(const queue<_Tp1, _Container1>& __l, const queue<_Tp1, _Container1>& __r)
    {
        return !(__l._c == __r._c);
    }

}


#endif
