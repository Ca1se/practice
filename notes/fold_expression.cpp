// Fold Expression (Since C++17)
//
// 1) Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
// 2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
// 3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN−1 op (EN op I))))
// 4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)
//


#include <iostream>
#include <cstddef>

namespace test {

template <size_t... Inputs>
constexpr size_t accumulate = (... + Inputs);

template <typename ...Args>
void print_all_inputs(Args... inputs) {
    ((std::cout << inputs << " "), ..., (std::cout << "\n"));
}

}

int main() {
    test::print_all_inputs("1", "二", 3, 4.05);
    return 0;
}
