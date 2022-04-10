#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 50000 + 5;
int n, m, p, l, r, c;
int w[maxn];

struct Edge {
	Edge(int f, int t): f(f), t(t) {}
	int f, t;
};
vector<Edge> edges;
vector<int> efrom[maxn];

int tot = 0;
int dfn[maxn], id[maxn];
int heavy_son[maxn], father[maxn];
int sub_size[maxn], deep[maxn], top[maxn];
int seg[maxn << 2], lazy[maxn << 2];

void Add(int f, int t) {
	int r = edges.size();
	efrom[f].push_back(r);
	efrom[t].push_back(r);
	edges.emplace_back(f, t);
}

int TreeBuild(int r, int dep) {
	heavy_son[r] = 0;
	sub_size[r] = 1;
	deep[r] = dep;

	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == father[r]) continue;
		father[target] = r;
		sub_size[r] += TreeBuild(target, dep + 1);
		if(sub_size[heavy_son[r]] < sub_size[target]) {
			heavy_son[r] = target;
		}
	}
	return sub_size[r];
}

void TreeDecomposition(int r, int tp) {
	top[r] = tp;
	id[r] = ++tot;	
	dfn[id[r]] = r;

	if(heavy_son[r]) {
		TreeDecomposition(heavy_son[r], tp);
		for(int i = 0; i < efrom[r].size(); i++) {
			const auto& e = edges[efrom[r][i]];
			int target = e.f + e.t - r;
			if(target == heavy_son[r] || target == father[r]) continue;
			TreeDecomposition(target, target);
		}
	}
}

void Build(int f, int t, int p) {
	if(f == t) {
		seg[p] = w[dfn[f]];
		return;
	}

	int m = f + ((t - f) >> 1);
	Build(f, m, p << 1);
	Build(m + 1, t, (p << 1) | 1);
	seg[p] = seg[p << 1] + seg[(p << 1) | 1];
}

void CheckLazy(int f, int t, int m, int p) {
	if(lazy[p] && f != t) {
		seg[p << 1] += (m - f + 1) * lazy[p];
		seg[(p << 1) | 1] += (t - m) * lazy[p];
		lazy[p << 1] += lazy[p];
		lazy[(p << 1) | 1] += lazy[p];
		lazy[p] = 0;
	}
}

void Update(int f, int t, int p) {
	if(l <= f && t <= r) {
		seg[p] += (t - f + 1) * c;
		lazy[p] += c;
		return;
	}

	int m = f + ((t - f) >> 1);
	CheckLazy(f, t, m, p);
	if(l <= m) Update(f, m, p << 1);
	if(m < r) Update(m + 1, t, (p << 1) | 1);
	seg[p] = seg[p << 1] + seg[(p << 1) | 1];
}

void Change(int x, int y) {
	while(top[x] != top[y]) {
		if(deep[top[x]] > deep[top[y]]) swap(x, y);
		l = id[top[y]], r = id[y];
		Update(1, tot, 1);
		y = father[top[y]];
	}
	if(id[x] > id[y]) swap(x, y);
	l = id[x], r = id[y];
	Update(1, tot, 1);
}

ll Query(int f, int t, int p) {
	if(f == t && f == l) {
		return seg[p];
	}
	int m = f + ((t - f) >> 1);
	CheckLazy(f, t, m, p);
	if(l <= m) return Query(f, m, p << 1);
	else return Query(m + 1, t, (p << 1) | 1);
}

int main() {
	char q;
	int pre = 0;
	while(~scanf("%d%d%d", &n, &m, &p)) {
		tot = 0;
		edges.clear();
		for(int i = 1; i <= pre; i++) {
			efrom[i].clear();
		}
		memset(lazy, 0, sizeof lazy);
		pre = n;
		for(int i = 1; i <= n; i++) {
			scanf("%d", w + i);
		}
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &l, &r);
			Add(l, r);
		}

		father[1] = 0;
		sub_size[0] = 0;
		top[0] = 0;
		TreeBuild(1, 1);
		TreeDecomposition(1, 1);

		Build(1, tot, 1);

		while(p--) {
			scanf(" %c", &q);
			if(q == 'Q') {
				scanf("%d", &l);
				l = id[l];
				printf("%lld\n", Query(1, tot, 1));
			}else {
				scanf("%d%d%d", &l, &r, &c);
				if(q == 'D') c = -c;
				Change(l, r);
			}
		}
	}
	return 0;
}
