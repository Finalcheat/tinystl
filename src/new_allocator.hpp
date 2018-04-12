#ifndef _TINYSTL_NEW_ALLOCATOR_HPP_
#define _TINYSTL_NEW_ALLOCATOR_HPP_ 1

#include <new>


namespace tinystl {

    using std::size_t;
    using std::ptrdiff_t;

    template<typename _Tp>
    class new_allocator
    {

    public:
        typedef size_t       size_type;
        typedef ptrdiff_t    difference_type;
        typedef _Tp*         pointer;
        typedef const _Tp*   const_pointer;
        typedef _Tp&         reference;
        typedef const _Tp&   const_reference;
        typedef _Tp          value_type;

        template<typename _Tp1>
        struct rebind { typedef new_allocator<_Tp1> other; };

        new_allocator() throw() {}

        template<typename _Tp1>
        new_allocator(new_allocator<_Tp1>&) throw() {}

        pointer address(reference __x) const { return &__x; }

        const_pointer address(const_reference __x) const { return &__x; }

        pointer allocate(size_type __n, const void* = 0)
        {
            return static_cast<pointer>(::operator new(__n * sizeof(value_type)));
        }

        void deallocate(pointer __p, size_type) { ::operator delete(__p); }

        size_type max_size() const { return size_t(-1) / sizeof(value_type); }

        void construct(pointer __p, const_reference __val) { ::new(__p) value_type(__val); }

        void destroy(pointer __p) { __p->~_Tp(); }

    };

    template<typename _Tp>
    inline bool operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&) { return true; }

    template<typename _Tp>
    inline bool operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&) { return false; }

}


#endif
