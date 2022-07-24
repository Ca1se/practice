#include <cstdio>

namespace crtp {

template <typename Derived>
class base {
public:
    void declear() {
        static_cast<Derived*>(this)->declear_impl();
    }
};

class derived1: public base<derived1> {
public:
    void declear_impl() {
        printf("derive1\n");
    }
};

class derived2: public base<derived2> {
public:
    void declear_impl() {
        printf("derive2\n");
    }
};

}

template <typename T>
void foo(crtp::base<T>* ptr) {
    ptr->declear();
}


int main() {
    auto d1 = new crtp::derived1;
    auto d2 = new crtp::derived2;
    foo(d1);
    foo(d2);
    delete d1;
    delete d2;
    return 0;
}
