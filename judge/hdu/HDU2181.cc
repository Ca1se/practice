#include <bits/stdc++.h>
using namespace std;
struct Edge {
	Edge(int f, int t): f(f), t(t) {}
	int f, t;
};
int cnt;
vector<Edge> edges;
vector<int> efrom[21];
vector<int> p;
bool vis[21] = {};
bool v[21][21] = {};

void Add(int x, int y) {
	if(v[x][y]) return;
	v[x][y] = v[y][x] = true;
	int len = edges.size();
	efrom[x].push_back(len);
	efrom[y].push_back(len);
	edges.emplace_back(x, y);
}

void dfs(int r) {
	bool jug = false;
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == p[0]) jug = true;
		if(vis[target]) continue;
		vis[target] = true;
		p.push_back(target);
		dfs(target);
		p.pop_back();
		vis[target] = false;
	}
	if(p.size() == 20 && jug) {
		printf("%d: ", ++cnt);
		for(int i = 0; i < p.size(); i++) {
			printf(" %d", p[i]);
		}
		printf(" %d\n", p[0]);
	}
}

int main() {
	int x1, x2, x3, m;
	for(int i = 1; i <= 20; i++) {
		scanf("%d%d%d", &x1, &x2, &x3);
		Add(i, x1), Add(i, x2), Add(i, x3);
	}
	for(int i = 1; i <= 20; i++) {
		sort(efrom[i].begin(), efrom[i].end(), [](int x, int y) {
			const auto& e1 = edges[x], e2 = edges[y];
			return (e1.f + e1.t) < (e2.f + e2.t);
		});
	}
	while(scanf("%d", &m), m) {
		cnt = 0;
		vis[m] = true;
		p.push_back(m);
		dfs(m);
		vis[m] = false;
		p.pop_back();
	}

	return 0;
}
