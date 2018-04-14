#ifndef _TINYSTL_STACK_HPP_
#define _TINYSTL_STACK_HPP_ 1

#include "vector.hpp"


namespace tinystl {

    template<typename _Tp, typename _Container = tinystl::vector<_Tp> >
    class stack
    {
    public:
        typedef typename _Container::value_type       value_type;
        typedef typename _Container::reference        reference;
        typedef typename _Container::const_reference  const_reference;
        typedef typename _Container::size_type        size_type;

    public:
        template<typename _Tp1, typename _Container1>
        friend bool operator==(const stack<_Tp1, _Container1>&, const stack<_Tp1, _Container1>&);

    public:
        explicit stack(const _Container& __c = _Container()) : _c(__c) { }

    public:
        bool empty() const
        {
            return _c.empty();
        }

        size_type size() const
        {
            return _c.size();
        }

        reference top()
        {
            return _c.back();
        }

        void push(const value_type& __v)
        {
            _c.push_back(__v);
        }

        void pop()
        {
            _c.pop_back();
        }

    protected:
        _Container _c;
    };


    template<typename _Tp1, typename _Container1>
    bool operator==(const stack<_Tp1, _Container1>& __l, const stack<_Tp1, _Container1>& __r)
    {
        return __l._c == __r._c;
    }

    template<typename _Tp1, typename _Container1>
    bool operator!=(const stack<_Tp1, _Container1>& __l, const stack<_Tp1, _Container1>& __r)
    {
        return !(__l._c == __r._c);
    }

}


#endif
