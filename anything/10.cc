//令operator= 返回一个reference to *this
#include<bits/stdc++.h>
class Integer {
public:
    Integer& operator= (const Integer& rhs) {
        this->value = rhs.value;
        return *this;
    }
    Integer& operator= (int val) {
        this->value = val;
        return *this;
    }
private:
    int value;
    friend std::ostream& operator<< (std::ostream& os, const Integer& rhs);
};
std::ostream& operator<< (std::ostream& os, const Integer& rhs) {
    os << rhs.value;
    return os;
}
int main() {
    Integer a, b;
    a = b = 1;
    std::cout << a << b << std::endl;
}