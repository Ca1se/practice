#ifndef _MY_TYPE_TRAITS_H_
#define _MY_TYPE_TRAITS_H_

namespace my {

struct _true_type {};
struct _false_type {};

template<typename ValueT>
struct _type_traits {
    using has_trivial_default_constructor   = _false_type;
    using has_trivial_copy_constructor      = _false_type;
    using has_trivial_assignment_operator   = _false_type;
    using has_trivial_destructor            = _false_type;
    using is_POD_type                       = _false_type;
};

template<>
struct _type_traits<char> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<signed char> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<unsigned char> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<int> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<unsigned int> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<short> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<unsigned short> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<long> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<unsigned long> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<float> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<double> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<>
struct _type_traits<long double> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;
};

template<typename ValueT>
struct _type_traits<ValueT*> {
    using has_trivial_default_constructor   = _true_type;
    using has_trivial_copy_constructor      = _true_type;
    using has_trivial_assignment_operator   = _true_type;
    using has_trivial_destructor            = _true_type;
    using is_POD_type                       = _true_type;

};

}

#endif
