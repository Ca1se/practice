#ifndef _MY_UNINITIALIZED_H_
#define _MY_UNINITIALIZED_H_

/* date: 2021.7.6
 * author: Ye Wu
 * function: Implement the duplication and filling of container elements
 */

#include <algorithm>
#include <cstring>
#include "my_type_traits.h"
#include "my_construct.h"
#include "my_iterator_traits.h"

namespace my {

template<typename ForwardIterator, typename ValueT, typename RawT>
inline ForwardIterator
_uninitialized_fill_n(ForwardIterator begin, size_t n,
                      const ValueT& val, RawT*) {
    using is_POD = typename _type_traits<RawT>::is_POD_type;
    return _uninitialized_fill_n_aux(begin, n, val, is_POD());
}

template<typename ForwardIterator, typename ValueT>
inline ForwardIterator
uninitialized_fill_n(ForwardIterator begin, std::size_t n,
        const ValueT& val) {
    return _uninitialized_fill_n(begin, n, val, value_type(begin));
}

template<typename ForwardIterator, typename ValueT>
inline ForwardIterator
_uninitialized_fill_n_aux(ForwardIterator begin, size_t n,
        const ValueT& val, _true_type) {
    for(; n > 0; n--, begin++) {
        *begin = val;
    }
    return begin;
}

template<typename ForwardIterator, typename ValueT>
inline ForwardIterator
_uninitialized_fill_n_aux(ForwardIterator begin, size_t n,
        const ValueT& val, _false_type) {
    for(; n > 0; n--, begin++) {
        construct(&*begin, val);
    }
    return begin;
}


template<typename ForwardIterator, typename ValueT, typename RawT>
inline void
_uninitialized_fill(ForwardIterator begin, ForwardIterator end,
                    const ValueT& val, RawT*) {
    using is_POD = typename _type_traits<RawT>::is_POD_type;
    _uninitialized_fill_aux(begin, end, val, is_POD());
}

template<typename ForwardIterator, typename ValueT>
inline void
uninitialized_fill(ForwardIterator begin, ForwardIterator end,
        const ValueT& val) {
    _uninitialized_fill(begin, end, val, value_type(begin));
}

template<typename ForwardIterator, typename ValueT>
inline void
_uninitialized_fill_aux(ForwardIterator begin, ForwardIterator end,
        const ValueT& val, _true_type) {
    for(; begin != end; begin++) {
        *begin = val;
    }
}

template<typename ForwardIterator, typename ValueT>
inline void
_uninitialized_fill_aux(ForwardIterator begin, ForwardIterator end,
        const ValueT& val, _false_type) {
    for(; begin != end; begin++) {
        construct(&*begin, val);
    }
}

template<typename InputIterator, typename ForwardIterator, typename RawT>
inline ForwardIterator
_uninitialized_copy(InputIterator begin, InputIterator end,
                    ForwardIterator result, RawT*) {
    using is_POD = typename my::_type_traits<RawT>::is_POD_type;
    return _uninitialized_copy_aux(begin, end, result, is_POD());
}

template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy(InputIterator begin, InputIterator end,
        ForwardIterator result) {
    return _uninitialized_copy(begin, end, result, value_type(result));
}

template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator
_uninitialized_copy_aux(InputIterator begin, InputIterator end,
        ForwardIterator result, _true_type) {
    return std::copy(begin, end, result);
}

template<typename InputIterator, typename ForwardIterator>
inline ForwardIterator
_uninitialized_copy_aux(InputIterator begin, InputIterator end,
        ForwardIterator result, _false_type) {
    ForwardIterator cur = result;
    for(; begin != end; begin++, cur++) {
        construct(&*cur, *begin);
    }
    return cur;
}

// special handling for char* and wchar_t*
inline char*
uninitialized_copy(const char* begin, const char* end,
        char* result) {
    memmove(result, begin, end - begin);
    return result + (end - begin);
}

inline wchar_t*
uninitialized_copy(const wchar_t* begin, const wchar_t* end,
        wchar_t* result) {
    memmove(result, begin, (end - begin) * sizeof(wchar_t));
    return result + (end - begin);
}

} // namespace my

#endif
