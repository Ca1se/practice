#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int maxn = 3005;
ll trs[maxn];
ll S[maxn][maxn] = {}, fac[maxn], inv[maxn];
ll Add(ll x, ll y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
void gettrs() {
	int r = 1;
	trs[0] = 1;
	while(r != 3001) {
		trs[r] = trs[r - 1] * r % mod;
		r++;
	}
}

ll qpow(int n, int m) {
    ll ans = 1;
    while(m){
        if(m & 1)   ans = ans * n % mod;
        m >>= 1;
        n = n * n % mod;
    }
    return ans;
}


void pre() {
	S[1][1] = 1;
	for(int i = 2; i <= 3000; ++i)
		for(int j = 1; j <= i; ++j)
			S[i][j] = Add(S[i-1][j-1], S[i-1][j] * j % mod);
}

int main() {
	int t, n, m;
	gettrs();
	pre();
	scanf("%d", &t);
	while(t--) {
		ll as = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			for(int k = max(i - 1, 1); k <= min(i + 1, m); k++) {
				as = (as + S[n][i] * S[m][k] % mod * trs[i] % mod * trs[k] % mod * (i == k ? 2 : 1) % mod) % mod;
			}
		}
		printf("%lld\n", as);
	}
	return 0;
}
