#include <bits/stdc++.h>
using namespace std;
int main() {
    int t, n, s;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &s);
        printf("%d\n", s / (int) (n - ceil(n / 2.0) + 1));
    }
    return 0;
}
