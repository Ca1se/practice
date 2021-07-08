#ifndef _MY_ITERATOR_TRAITS_H_
#define _MY_ITERATOR_TRAITS_H_

/* date: 2021.7.7
 * author: Ye Wu
 * function: 
 * description: A very simple iterator(In fact, just pointer) traits header in order to implement a vector
 */

#include <cstddef>

struct random_access_iterator_tag {};

template<typename Iterator>
struct iterator_traits {
    using iterator_category = typename Iterator::iterator_category;
    using value_type        = typename Iterator::value_type;
    using difference_type   = typename Iterator::difference_type;
    using pointer           = typename Iterator::pointer;
    using reference         = typename Iterator::reference;
};

// partial specialization
template<typename ValueT>
struct iterator_traits<ValueT*> {
    using iterator_category = random_access_iterator_tag;
    using value_type        = ValueT;
    using difference_type   = ptrdiff_t;
    using pointer           = ValueT*;
    using reference         = ValueT&;
};

// get iterator's raw type
template<typename Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
    return static_cast<typename iterator_traits<Iterator>::value_type*>(nullptr);
}

#endif
