#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 5;
int arr[maxn];
int main() {
    int t, n, k;
    ll ans = -1e5 * 100 - 100;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; i++) {
            scanf("%d", arr + i);
        } 
        for(int i = max(1, n - 2 * k); i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                ans = max(ans, (ll) i * j - (ll) k * (arr[i] | arr[j]));
            }
        }
        printf("%lld\n", ans);
        ans = -1e5 * 100 - 100;
    }
    return 0;
}
