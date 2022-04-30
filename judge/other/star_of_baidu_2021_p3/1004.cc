#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 80 + 5;
int n;
bool vis[maxn];

/*
void dfs(int pos, int round) {
	if(round == n) {
		ans++;
		return;
	}
	int a = (pos + round) % n;
	if(!vis[a]) {
		vis[a] = true;
		dfs(a, round + 1);
		vis[a] = false;
	}
	a = (pos - round + n) % n;
	if(!vis[a]) {
		vis[a] = true;
		dfs(a, round + 1);
		vis[a] = false;
	}
}
*/
int ans[] = {0, 1, 2, 2, 4, 2, 4, 4, 8, 2, 4, 6, 8, 2, 8, 6, 16, 2, 4, 6, 8, 4, 12, 6, 16, 4, 4, 4, 16, 2, 12, 10, 32, 4, 4, 8, 8, 2, 12, 6, 16, 2, 8, 6, 24, 6, 12, 8, 32, 6, 8, 6, 8, 2, 8, 10, 32, 4, 4, 6, 24, 2, 20, 6, 64, 6, 8, 8, 8, 4, 16, 6, 16, 2, 4, 8, 24, 14, 12, 6, 32};

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	
	return 0;
}
