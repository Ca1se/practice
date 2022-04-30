#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2 * 1e5 + 5;
const int maxm = 20 + 5;
char s[maxm];
int n, m;
ll a[(1 << maxm) + 5] = {}, k, ans = 0;

void Fwt_xor(ll* a, int n, int opt) {
    for(int k = 1; k < n; k <<= 1) {
        for(int p = k << 1, i = 0; i < n; i += p) {
            for(int j = 0; j < k ; j++) {
                ll x = a[i + j], y = a[i + j + k];
                a[i + j] = x + y, a[i + j + k] = x - y;
                if(!opt) a[i + j] >>= 1, a[i + j + k] >>= 1;
            }
        }
    }
}

int main() {
    scanf("%d%d%lld", &n, &m, &k);
    for(int i = 0; i < n; i++) {
        scanf("%s", s); int S = 0;
        for(int j = 0; j < m; j++) if(s[j] == 'B') S |= 1 << j;
        a[S]++;
    }
    
    Fwt_xor(a, 1 << m, 1);
    for(int i = 0; i < (1 << m); i++) a[i] = a[i] * a[i];
    Fwt_xor(a, 1 << m, 0);
    a[0] -= n;
    for(int i = 0; i < (1 << m); i++) a[i] >>= 1;
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < (1 << m); i++) {
            if((i >> j) & 1) a[i] += a[i ^ (1 << j)];
        }
    }
    ll all = ((ll) n * (n - 1)) >> 1;
    for(int i = 1; i < (1 << m); i++) if(all - a[i ^ ((1 << m) - 1)] >= k) ans++;
    printf("%lld\n", ans);
    return 0;
}

