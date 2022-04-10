#include <bits/stdc++.h>
#define ll long long
using namespace std;
int getl(int r) {
    if(!r) return 1;
    int i = 0;
    for(; r; r >>= 1, i++);
    return i;
}
int main() {
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        ll ans = 0;
        scanf("%d%d", &n, &m);
        m++;
        int ml = max(getl(n), getl(m));
        for(int i = ml - 1; i >= 0; i--) {
            int u = n & (1 << i), d = m & (1 << i);
            if(u > d) {
                break;
            }else if(u < d) {
                ans |= (1 << i);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
