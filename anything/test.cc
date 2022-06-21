#include <cstdio>
#include <iostream>

class A {
public:
    constexpr A() = default;
    constexpr ~A() = default;
};

int main() {
    int a;
    scanf("%d", &a);
    constexpr int b = a;
}
