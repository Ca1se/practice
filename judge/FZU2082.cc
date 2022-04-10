#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 50000 + 5;

struct Edge {
	int from, to, weight;
	Edge(int f, int t, int w): from(f), to(t), weight(w) {}
};
vector<Edge> edges;
vector<int> efrom[maxn];
int n, m, f, t, w, q;
int father[maxn], deep[maxn], heavy_len[maxn];
int top[maxn], heavy_son[maxn], len[maxn], sub_size[maxn];

inline void add(int x, int y) {
	int l = edges.size();
	efrom[x].push_back(l);
	efrom[y].push_back(l);
	edges.emplace_back(f, t, w);
}

int TreeBuild(int r, int dep) {
	heavy_son[r] = 0;
	deep[r] = dep;
	sub_size[r] = 1;

	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.from + e.to - r;
		if(target == father[r]) continue;
		father[target] = r;
		sub_size[r] += TreeBuild(target, dep + 1);
		if(sub_size[heavy_son[r]] < sub_size[target]) {
			heavy_son[r] = target;
			heavy_len[r] = e.weight;
		}
	}

	return sub_size[r];
}

void TreeDecomposition(int r, int w, int tp) {
	top[r] = tp;
	if(top[father[r]] == tp) len[r] = len[father[r]] + w;
	else len[r] = w;

	if(heavy_son[r]) {
		TreeDecomposition(heavy_son[r], heavy_len[r], tp);
		for(int i = 0; i < efrom[r].size(); i++) {
			const auto& e = edges[efrom[r][i]];
			int target = e.from + e.to - r;
			if(target == father[r] || target == heavy_son[r]) continue;
			TreeDecomposition(target, e.weight, target);
		}
	}
}

void update(int r) {
	int fa = father[r];
	if(top[r] != top[fa]) {
		len[r] = t;
	}else {
		len[r] = len[fa] + heavy_len[fa];
	}
	if(heavy_son[r]) {
		update(heavy_son[r]);
	}
}

void modify(int p) {
	auto& e = edges[p - 1];
	int x = deep[e.from] > deep[e.to] ? e.from : e.to;
	if(top[e.from] == top[e.to]) heavy_len[e.from + e.to - x] = t;
	update(x);
}

ll query(int x, int y) {
	ll res = 0;
	while(top[x] != top[y]) {
		int xtop = top[x], ytop = top[y];
		if(deep[xtop] > deep[ytop]) swap(x, y), swap(xtop, ytop);
		res += len[y];
		y = father[ytop];
	}
	return res + abs(len[x] - len[y]);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n - 1; i++) {
		scanf("%d%d%d", &f, &t, &w);
		add(f, t);
	}

	father[1] = 0;
	sub_size[0] = 0;
	TreeBuild(1, 1);

	top[0] = 0;
	TreeDecomposition(1, 0, 1);

	for(int i = 0; i < m; i++) {
		scanf("%d%d%d", &q, &f, &t);
		if(q) {
			printf("%lld\n", query(f, t));
		}else {
			modify(f);
		}
	}

	return 0;
}
