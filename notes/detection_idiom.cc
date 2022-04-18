// 2022/4/18

#include <experimental/type_traits>
#include <utility>
#include <iostream>

// c++ fundamental TS v2
template <typename T>
using get_t = decltype(std::declval<T>().get());

template <typename T>
using supports_get = std::experimental::is_detected<get_t, T>;

// c++ 11
template <typename T>
struct has_func_get {
    template <typename U>
    static constexpr
    decltype(std::declval<U>().get(), bool())
    detect_get(int) noexcept { return true; }

    template <typename U>
    static constexpr bool
    detect_get(...) noexcept { return false; }

    static constexpr bool value = detect_get<T>(int());
};

struct A {};

struct B {
    void get() const noexcept {}
};


int main() {
    std::cout << "c++ fundamental TS v2" << std::endl;
    std::cout << supports_get<A>::value << std::endl;
    std::cout << supports_get<B>::value << std::endl;

    std::cout << "c++ 11" << std::endl;
    std::cout << has_func_get<A>::value << std::endl;
    std::cout << has_func_get<B>::value << std::endl;

    return 0;
}
