#ifndef _MY_CONSTRUCT_H_
#define _MY_CONSTRUCT_H_

#include <new>
#include <utility>
#include "my_type_traits.h"
#include "my_iterator_traits.h"

namespace my {

template<typename ValueT, typename... Args>
inline void construct(ValueT* p, Args&&... args) {
    new(p) ValueT(std::forward<Args>(args)...);
}

template<typename ValueT>
inline void destroy(ValueT* p) {
    p->~ValueT();
}

template<typename Iterator, typename ValueT>
inline void _destroy(Iterator from, Iterator to, ValueT*) {
    using trivial_destructor = typename _type_traits<ValueT>::has_trivial_destructor;
    _destroy_aux(from, to, trivial_destructor());
}

template<typename Iterator>
inline void destroy(Iterator from, Iterator to) {
    _destroy(from, to, value_type(from));
}



template<typename Iterator>
inline void _destroy_aux(Iterator /* from */, Iterator /* to */, _true_type) {}

template<typename Iterator>
inline void _destroy_aux(Iterator from, Iterator to, _false_type) {
    for(; from < to; from++) {
        destroy(&*from);
    }
}

} // namespace my

#endif
