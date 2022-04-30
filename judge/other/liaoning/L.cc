#include <bits/stdc++.h>
using namespace std;
int main() {
    int t, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &x);
        printf("%d\n", min(18, x));
    }
    return 0;
}
