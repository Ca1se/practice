#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll t, n;
    scanf("%lld", &t);
    while(t--) {
        scanf("%lld", &n);
        ll ans = n - (n / 2 + 1) + 1;
        ll front = ceil((double) (n - 1) / 3);
        if((n - 1) % 3 == 0 && (n & 1) == 0) front += 2;
        if((front & 1) == 0) front++;
        ll last = (n & 1) ? n : n - 1;
        ans += (last + 1) / 2 - (front + 1) / 2 + 1;
        printf("%lld\n", ans);
    }
    return 0;
}
