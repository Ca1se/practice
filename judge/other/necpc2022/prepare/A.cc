#include <iostream>
#include <cstdio>

using ll = long long;

inline ll fast_pow(ll a, ll b, int mod) {
    ll ret = 1;
    ll tmp = a % mod;
    while(b > 0) {
        if(b & 1) ret = ret * tmp % mod;
        b >>= 1;
        tmp = tmp * tmp % mod;
    }
    return ret;
}

inline ll fast_pow1(ll a, ll b) {
    ll ret = 1;
    ll tmp = a;
    while(b > 0) {
        if(b & 1) ret = ret * tmp;
        b >>= 1;
        tmp = tmp * tmp;
    }
    return ret;
}

int main() {
    int t;
    scanf("%d", &t);
    ll x, y, z;
    while(t--) {
        scanf("%lld%lld%lld", &x, &y, &z);
        ll x1 = x % 10;
        if(x1 == 1 || x1 == 5 || x1 == 0 || x1 == 6) {
            printf("%lld\n", x1);
        }else if(x1 == 4 || x1 == 9) {
            if(fast_pow(y, z, 2) == 1) {
                printf("%lld\n", x1);
            }else {
                printf("%lld\n", x1 * x1 % 10);
            }
        }else {
            ll tmp = fast_pow(y, z, 4);
            if(tmp == 1) {
                printf("%lld\n", x1);
            }else if(tmp == 2) {
                printf("%lld\n", x1 * x1 % 10);
            }else if(tmp == 3) {
                printf("%lld\n", x1 * x1 * x1 % 10);
            }else {
                printf("%lld\n", x1 * x1 * x1 * x1 % 10);
            }
        }
    }
    return 0;
}
