// 注意线段树区间范围问题，当给定的值不是点值而是范围值时，两点在同一条链上时，l要+1，因为一个结点的值其实代表它与它的父结点的边权，当我们想negate (2, 4) 我们实际应该negate(3, 4) 因为3的值代表了2与3边的权重 
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000 + 5;

struct Edge {
	Edge(int f, int t, int w): f(f), t(t), w(w) {}
	int f, t, w;
};

vector<Edge> edges;
vector<int> efrom[maxn];

int tot = 0, l, r, c;
int sub_size[maxn], heavy_son[maxn], heavy_len[maxn], father[maxn], deep[maxn], top[maxn], id[maxn], dfw[maxn];
int segmax[maxn << 2], segmin[maxn << 2], lazy[maxn << 2];

inline void scanff(int& x) {
	x = 0;
	int ch = getchar(), sg = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-') sg = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	x *= sg;
}

void Add() {
	int len = edges.size();
	efrom[l].push_back(len);
	efrom[r].push_back(len);
	edges.push_back(Edge(l, r, c));
}

int BuildTree(int r, int dep) {
	heavy_son[r] = 0;
	sub_size[r] = 1;
	deep[r] = dep;

	for(int i = 0; i < efrom[r].size(); i++) {
		const Edge& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == father[r]) continue;
		father[target] = r;
		sub_size[r] += BuildTree(target, dep + 1);
		if(sub_size[heavy_son[r]] < sub_size[target]) {
			heavy_son[r] = target;
			heavy_len[r] = e.w;
		}
	}
	return sub_size[r];
}

void TreeDecomposition(int r, int w, int tp) {
	top[r] = tp;
	id[r] = ++tot;
	dfw[id[r]] = w;

	if(heavy_son[r]) {
		TreeDecomposition(heavy_son[r], heavy_len[r], tp);
		for(int i = 0; i < efrom[r].size(); i++) {
			const Edge& e = edges[efrom[r][i]];
			int target = e.f + e.t - r;
			if(target == father[r] || target == heavy_son[r]) continue;
			TreeDecomposition(target, e.w, target);
		}
	}
}

void PushUp(int p) {
	segmax[p] = max(segmax[p << 1], segmax[(p << 1) | 1]);
	segmin[p] = min(segmin[p << 1], segmin[(p << 1) | 1]);
}

void Build(int f, int t, int p) {
	if(f == t) {
		segmax[p] = segmin[p] = dfw[f];
		lazy[p] = 0;
		return;
	}

	int m = f + ((t - f) >> 1);
	Build(f, m, p << 1);
	Build(m + 1, t, (p << 1) | 1);
	PushUp(p);
	lazy[p] = 0;
}

inline void Exchange(int& x, int& y) {
	swap(x, y);
	x = -x;
	y = -y;
}

void CheckLazy(int f, int t, int m, int p) {
	if(lazy[p]) {
		Exchange(segmax[p << 1], segmin[p << 1]);
		Exchange(segmax[(p << 1) | 1], segmin[(p << 1) | 1]);
		lazy[p << 1] ^= 1;
		lazy[(p << 1) | 1] ^= 1;
		lazy[p] = 0;
	}
}

void Update(int f, int t, int p) {
	if(f == t) {
		segmax[p] = segmin[p] = c;
		return;
	}
	int m = f + ((t - f) >> 1);
	CheckLazy(f, t, m, p);
	if(l <= m) Update(f, m, p << 1);
	else Update(m + 1, t, (p << 1) | 1);
	PushUp(p);
}

void Negate(int f, int t, int p) {
	if(l <= f && t <= r) {
		Exchange(segmax[p], segmin[p]);
		lazy[p] ^= 1;
		return;
	}
	int m = f + ((t - f) >> 1);
	CheckLazy(f, t, m, p);
	if(l <= m) Negate(f, m, p << 1);
	if(m < r) Negate(m + 1, t, (p << 1) | 1);
	PushUp(p);
}

void Neg(int x, int y) {
	while(top[x] != top[y]) {
		if(deep[top[x]] > deep[top[y]]) swap(x, y);
		l = id[top[y]], r = id[y];
		Negate(2, tot, 1);
		y = father[top[y]];
	}
	if(x == y) return;
	if(id[x] > id[y]) swap(x, y);
	l = id[x] + 1, r = id[y];
	Negate(2, tot, 1);
}

int Query(int f, int t, int p) {
	if(l <= f && t <= r) {
		return segmax[p];
	}
	int m = f + ((t - f) >> 1);
	CheckLazy(f, t, m, p);
	int ans = -0x7fffffff;
	if(l <= m) ans = Query(f, m, p << 1);
	if(m < r) ans = max(ans, Query(m + 1, t, (p << 1) | 1));
	PushUp(p);
	return ans;
}

int Ask(int x, int y) {
	int ans = -0x7fffffff;
	while(top[x] != top[y]) {
		if(deep[top[x]] > deep[top[y]]) swap(x, y);
		l = id[top[y]], r = id[y];
		ans = max(ans, Query(2, tot, 1));
		y = father[top[y]];
	}
	if(x == y) return ans;
	if(id[x] > id[y]) swap(x, y);
	l = id[x] + 1, r = id[y];
	ans = max(ans, Query(2, tot, 1));
	return ans;
}

int main() {
	int t, n, pre = 0;
	char str[10];
	scanff(t);
	while(t--) {
		tot = 0;
		edges.clear();
		for(int i = 1; i <= pre; i++) {
			efrom[i].clear();
		}
		scanff(n);
		pre = n;
		for(int i = 0; i < n - 1; i++) {
			scanff(l), scanff(r), scanff(c);
			Add();
		}
		father[1] = sub_size[0] = 0;
		BuildTree(1, 1);
		TreeDecomposition(1, 0, 1);
		Build(2, tot, 1);
		
		while(scanf("%s", str) && str[0] != 'D') {
			if(str[0] == 'Q') {
				scanff(l), scanff(r);
				printf("%d\n", Ask(l, r));
			}else if(str[0] == 'C') {
				scanff(l), scanff(c);
				const Edge& e = edges[l - 1];
				l = deep[e.f] > deep[e.t] ? id[e.f] : id[e.t];
				Update(2, tot, 1);
			}else if(str[0] == 'N') {
				scanff(l), scanff(r);
				Neg(l, r);
			}		
		}
	}
	return 0;
}
