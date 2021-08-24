#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 3005;
const int mod = 1e9 + 7;
ll trs[maxn];
ll s[maxn][maxn];


void pre() {
	s[1][1] = 1;
	trs[0] = trs[1] = 1;
	for(int i = 2; i <= 3000; i++) {
		trs[i] = trs[i - 1] * i % mod;
		for(int k = 1; k <= i; k++) {
			s[i][k] = (s[i - 1][k - 1] + k * s[i - 1][k] % mod) % mod;
		}
	}
}

int main() {
	int t, n, m;
	pre();
	scanf("%d", &t);
	while(t--) {
		ll ans = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			for(int k = max(i - 1, 1); k <= min(i + 1, m); k++) {
				ans = (ans + s[n][i] * s[m][k] % mod * trs[i] % mod * trs[k] % mod * (i == k ? 2 : 1) % mod) % mod;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
