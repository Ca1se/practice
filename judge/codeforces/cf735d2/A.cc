#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
    ll ans = 0, pre, r;
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%lld", &n, &pre);
        for(int i = 1; i < n; i++) {
            scanf("%lld", &r);
            ans = max(ans, r * pre);
            pre = r;
        }
        printf("%lld\n", ans);
        ans = 0;
    }
    return 0;
}
