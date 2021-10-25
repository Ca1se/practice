#include <bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5;
int c[maxn];
int topo[maxn], t, n = 1;
bool G[maxn][maxn];
bool dfs(int u) {
	c[u] = -1;
	for(int v = 1; v < n; v++) if(G[u][v]) {
		if(c[v] < 0) return false;
		else if(!c[v] && !dfs(v)) return false;
	}
	c[u] = 1; topo[--t] = u;
	return true;
}
bool toposort() {
	t = n;
	memset(c, 0, sizeof c);
	for(int u = 1; u < n; u++) {
		if(!c[u]) {
			if(!dfs(u)) return false;
		}
	}
	return true;
}
map<char, int> mp;
map<int, char> mpp;
char arr[10];
int main() {
	int r;
	scanf("%d", &r);
	for(int i = 0; i < r; i++) {
		scanf("%s", arr);
		if(mp[arr[0]] == 0) mp[arr[0]] = n, mpp[n++] = arr[0];
		if(mp[arr[2]] == 0) mp[arr[2]] = n, mpp[n++] = arr[2];
		if(mp[arr[3]] == 0) mp[arr[3]] = n, mpp[n++] = arr[3];
		G[mp[arr[0]]][mp[arr[2]]] = true;
		G[mp[arr[3]]][mp[arr[0]]] = true;
	}
	if(toposort()) {
    	for(int i = n - 1; i >= 1; i--) {
    		printf("%c", mpp[topo[i]]);
    	}
    	printf("\n");
	}else {
		printf("No Answer\n");
	}
	return 0;
}
