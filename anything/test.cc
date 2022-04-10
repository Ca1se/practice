#include <iostream>
#include <string>
using namespace std;

int main() {
    int a[3] = {10, 20, 30};

    int (&b)[3] = a;

    std::cout << (sizeof b) << std::endl;
    
    return 0;
}
