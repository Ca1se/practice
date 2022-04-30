#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    long long n, m, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld%lld%lld%lld", &n, &m, &x, &y);
        if(n != 1 && m != 1) {
            n--, m--;
            if(y >= 2 * x) printf("%lld\n", (n + m) * x);
            else {
                long long ans = 0;
                ans += min(n, m) * y;
                int last = abs(m - n);
                if(y < x) ans += (last / 2) * y * 2 + (last - last / 2 * 2) * x;
                else ans += last * x;
                printf("%lld\n", ans);
            }
        }else {
            n--, m--;
            printf("%lld\n", max(n, m) * x);
        }
    }
    return 0;
}
