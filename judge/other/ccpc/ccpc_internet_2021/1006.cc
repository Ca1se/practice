#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxl = 1e6 + 5;
const int mod = 998244353;
char mp[maxl];
ll cnt[maxl][11];
ll binpow(long long a, long long b) {
  if (b == 0) return 1;
  long long res = binpow(a, b / 2);
  if (b % 2)
    return ((res * res) % mod * a) % mod;
  else
    return (res * res) % mod;
}
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		ll ans = 0;
		scanf("%s", mp + 1);
		for(int i = 0; i <= 10; i++) cnt[0][i] = 0;
		int len = strlen(mp + 1);
		for(int i = 1; i <= len; i++) {
			for(int j = 1; j <= 10; j++) {
				cnt[i][j] = cnt[i - 1][j];
			}
			cnt[i][9] = 0;
			if(mp[i] == 'n') {
				cnt[i][1] = (cnt[i][1] + 1) % mod;
				cnt[i][3] = (cnt[i][3] + cnt[i - 1][2]) % mod;
			}else if(mp[i] == 'u') {
				cnt[i][2] =(cnt[i][2] + cnt[i - 1][1]) % mod;
			}else if(mp[i] == 'h') {
				cnt[i][4] = (cnt[i][4] + cnt[i - 1][3]) % mod;
				cnt[i][6] = (cnt[i][6] + cnt[i - 1][5]) % mod;
				cnt[i][7] = (cnt[i][7] + cnt[i - 1][6]) % mod;
				cnt[i][9] = cnt[i - 1][8];
			}else if(mp[i] == 'e') {
				cnt[i][5] = (cnt[i][5] + cnt[i - 1][4]) % mod;
				cnt[i][8] = (cnt[i][8] + cnt[i - 1][7]) % mod;
			}else if(mp[i] == 'a') {
				cnt[i][10] = (cnt[i][10] + 1) % mod;
			}
		}
		for(int i = 1; i <= len; i++) {
			ans = (ans + cnt[i][9] * (binpow(2, cnt[len][10] - cnt[i][10]) - 1) % mod) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
