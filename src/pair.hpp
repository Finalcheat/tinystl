#ifndef _TINYSTL_PAIR_HPP_
#define _TINYSTL_PAIR_HPP_ 1


namespace tinystl {

    template<typename _Tp1, typename _Tp2>
    struct pair
    {
        typedef _Tp1 first_type;
        typedef _Tp2 second_type;

        _Tp1 first;
        _Tp2 second;

        pair() : first(), second() { }

        pair(const _Tp1& __a, const _Tp2& __b) : first(__a), second(__b) { }

        template<typename _Tp3, typename _Tp4>
        pair(const pair<_Tp3, _Tp4>& __p) : first(__p.first), second(__p.second) { }
    };


    template<typename _Tp1, typename _Tp2>
    inline bool operator==(const pair<_Tp1, _Tp2>& __x, const pair<_Tp1, _Tp2>& __y)
    {
        return __x.first == __y.first && __x.second == __y.second;
    }


    template<typename _Tp1, typename _Tp2>
    inline bool operator!=(const pair<_Tp1, _Tp2>& __x, const pair<_Tp1, _Tp2>& __y)
    {
        return !(__x == __y);
    }


    template<typename _Tp1, typename _Tp2>
    inline bool operator<(const pair<_Tp1, _Tp2>& __x, const pair<_Tp1, _Tp2>& __y)
    {
        if (__x.first == __y.first)
        {
            return __x.second < __y.second;
        }
        return __x.first < __y.first;
    }


    template<typename _Tp1, typename _Tp2>
    inline bool operator>(const pair<_Tp1, _Tp2>& __x, const pair<_Tp1, _Tp2>& __y)
    {
        if (__x.first == __y.first)
        {
            return __x.second > __y.second;
        }
        return __x.first > __y.first;
    }


    template<typename _Tp1, typename _Tp2>
    inline bool operator<=(const pair<_Tp1, _Tp2>& __x, const pair<_Tp1, _Tp2>& __y)
    {
        return !(__x > __y);
    }


    template<typename _Tp1, typename _Tp2>
    inline bool operator>=(const pair<_Tp1, _Tp2>& __x, const pair<_Tp1, _Tp2>& __y)
    {
        return !(__x < __y);
    }

}


#endif
