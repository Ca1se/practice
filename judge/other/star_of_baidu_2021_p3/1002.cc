#include<bits/stdc++.h>
using namespace std;
const int maxn = 10 + 5;
int n;
char mp[maxn][maxn];
bool vis[maxn][maxn];
vector<pair<int, int>> s;
bool dfs(int x, int y, int opt) {
	if(x == 0 && y == 0) {
		if(!opt) {
			for(int i = 0; i < s.size() - 1; i++) {
				const auto&it = s[i];
				mp[it.second][it.first] = '#';
			}
		}
		return true;
	}
	vis[y][x] = true;

	int nx, ny;
	if(!opt) {
		nx = x, ny = y - 1;
		s.emplace_back(nx, ny);
		if(ny >= 0 && mp[ny][nx] == '.' && !vis[ny][nx] && dfs(nx, ny, opt)) return true;
		s.pop_back();
		nx = x - 1, ny = y;
		s.emplace_back(nx, ny);
		if(nx >= 0 && mp[ny][nx] == '.' && !vis[ny][nx] && dfs(nx, ny, opt)) return true;
		s.pop_back();
		return false;
	}else {
		nx = x - 1, ny = y;
		if(ny >= 0 && mp[ny][nx] == '.' && !vis[ny][nx] && dfs(nx, ny, opt)) return true;
		nx = x, ny = y - 1;
		if(nx >= 0 && mp[ny][nx] == '.' && !vis[ny][nx] && dfs(nx, ny, opt)) return true;
		else return false;
	}
}
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		s.clear();
		memset(vis, 0, sizeof vis);
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%s", mp + i);
		}
		if(mp[0][0] == '#' || mp[n - 1][n - 1] == '#') {
			printf("0\n");
			continue;
		}
		int ans = 0;
		if(mp[n - 2][n - 1] != '#') ans += int(dfs(n - 1, n - 2, 0));
		memset(vis, 0, sizeof vis);
		if(mp[n - 1][n - 2] != '#') ans += int(dfs(n - 2, n - 1, 1));
		printf("%d\n", ans);
	}
	return 0;
}
