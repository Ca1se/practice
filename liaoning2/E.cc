#include <bits/stdc++.h>
using namespace std;
const int maxn = 30 + 5;
int c[maxn][maxn];

long long anm(int n, int m) {
	long long res = 1;
	while(n--) {
		res *= m;
		m--;
	}
	return res;
}

inline long long getcnt(int n, int m) {
	if(c[n][m] != -1) return c[n][m];
	return c[n][m] = anm(n, m) / anm(n, n);
}

int main() {
	int n, m, t;
	memset(c, -1, sizeof c);
	scanf("%d%d%d", &n, &m, &t);
	long long ans = 0;
	for(int i = 4; i < min(n + 1, t); i++) {
		if(t - i > m) continue;
		ans += getcnt(i, n) * getcnt(t - i, m);
	}
	printf("%lld\n", ans);
	return 0;
}
