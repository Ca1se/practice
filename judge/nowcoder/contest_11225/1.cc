#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, pre, now;
    bool jud = true;
    scanf("%d", &n);
    scanf("%d", &pre);
    for(int i = 0; i < n - 1; i++) {
        scanf("%d", &now);
        if(__gcd(pre, now) != 1) {
            jud = false;
        }
        pre = now;
    }
    printf("%d\n", jud ? 0 : 1);

    return 0;
}

