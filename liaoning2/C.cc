#include <bits/stdc++.h>
using namespace std;
int arr[10];
int uf[10];
int cnt[10];

inline int Find(int p) {
	if(uf[p] == -1) return p;
	return (uf[p] = Find(uf[p]));
}

inline void Union(int x, int y) {
	uf[y] = x;
	cnt[x]++;
}
int main() {
	int t, n;
	scanf("%d", &t);
	while(t--) {
		memset(uf, -1, sizeof uf);
		memset(cnt, 0, sizeof cnt);
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d", arr + i);
		}
		sort(arr, arr + n);
		for(int i = 0; i < n - 1; i++) {
			if(abs(arr[i] - arr[i + 1]) <= 2) {
				Union(Find(i), i + 1);
			}
		}
		int minn = 34234234, maxx = 0;
		for(int i = 0; i < n; i++) {
			if(uf[i] == -1) {
				minn = min(minn, cnt[i]);
				maxx = max(maxx, cnt[i]);
			}
		}
		printf("%d %d\n", minn + 1, maxx + 1);
	}
	return 0;
}
