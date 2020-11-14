#include <bits/stdc++.h>
using namespace std;
void a() {
    printf("134");
}
void (*add(void ad()))() {
    return ad;
}
//void (* set_malloc_handler(void (*f)()))()
int main() {
    add(a)();
}