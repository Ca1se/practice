#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 30000 + 5;

int w[maxn];
struct Edge {
	Edge(int f, int t): f(f), t(t) {}
	int f, t;
};
vector<Edge> edges;
vector<int> efrom[maxn];

int tot, n, l, r, c;
int deep[maxn], sub_size[maxn], father[maxn], heavy_son[maxn], dfn[maxn], id[maxn], top[maxn];
int seg[maxn << 2];

void Add(int x, int y) {
	int r = edges.size();
	efrom[x].push_back(r);
	efrom[y].push_back(r);
	edges.emplace_back(x, y);
}

int TreeBuild(int r, int dep) {
	deep[r] = dep;
	sub_size[r] = 1;
	heavy_son[r] = 0;

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

void Update(int f, int t, int p) {
	if(f == t && f == l) {
		seg[p] = c;
		return;
	}
	int m = f + ((t - f) >> 1);
	if(l <= m) Update(f, m, p << 1);
	else Update(m + 1, t, (p << 1) | 1);
	seg[p] = seg[p << 1] + seg[(p << 1) | 1];
}

ll Query(int f, int t, int p) {
	if(l <= f && t <= r) {
		return seg[p];
	}
	int m = f + ((t - f) >> 1);
	ll sum = 0;
	if(l <= m) sum = Query(f, m, p << 1);
	if(m < r) sum += Query(m + 1, t, (p << 1) | 1);
	return sum;
}

ll Ask(int x, int y) {
	ll sum = 0;
	while(top[x] != top[y]) {
		if(deep[top[x]] > deep[top[y]]) swap(x, y);
		l = id[top[y]], r = id[y];
		sum += Query(1, tot, 1);
		y = father[top[y]];
	}
	if(id[x] > id[y]) swap(x, y);
	l = id[x], r = id[y];
	sum += Query(1, tot, 1);
	return sum;
}

int main() {
	int t, m, pre = 0, choose;
	scanf("%d", &t);
	for(int k = 1; k <= t; k++) {
		printf("Case %d:\n", k);
		tot = 0;
		edges.clear();
		for(int i = 1; i <= pre; i++) {
			efrom[i].clear();
		}
		scanf("%d", &n);
		pre = n;
		for(int i = 1; i <= n; i++) {
			scanf("%d", w + i);
		}
		for(int i = 0; i < n - 1; i++) {
			scanf("%d%d", &l, &r);
			l++, r++;
			Add(l, r);
		}

		sub_size[0] = 0;
		father[1] = 0;
		TreeBuild(1, 1);
		TreeDecomposition(1, 1);
		Build(1, tot, 1);
		scanf("%d", &m);
		while(m--) {
			scanf("%d", &choose);
			if(choose) {
				scanf("%d%d", &l, &c);
				l++;
				l = id[l];
				Update(1, tot, 1);
			}else {
				scanf("%d%d", &l, &r);
				l++, r++;
				printf("%lld\n", Ask(l, r));
			}
		}
	}
	return 0;
}
