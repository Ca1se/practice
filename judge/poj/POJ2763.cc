#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct Edge {
	Edge(int f, int t, int w): f(f), t(t), w(w) {}
	int f, t, w;
};
vector<Edge> edges;
vector<int> efrom[maxn];

int sub_size[maxn], heavy_son[maxn], top[maxn], father[maxn], deep[maxn], heavy_len[maxn], id[maxn], dfnw[maxn];
int seg[maxn << 2];
int n, q, s, l, r, w, tot = 0;

int TreeBuild(int r, int dep) {
	deep[r] = dep;
	sub_size[r] = 1;
	heavy_son[r] = 0;

	for(int i = 0; i < efrom[r].size(); i++) {
		const Edge& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == father[r]) continue;
		father[target] = r;
		sub_size[r] += TreeBuild(target, dep + 1);
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
	dfnw[id[r]] = w;

	if(heavy_son[r]) {
		TreeDecomposition(heavy_son[r], heavy_len[r], tp);
		for(int i = 0; i < efrom[r].size(); i++) {
			const Edge& e = edges[efrom[r][i]];
			int target = e.f + e.t - r;
			if(target == father[r] || target == heavy_son[r]) continue;
			TreeDecomposition(target , e.w, target);
		}
	}
}

void Build(int f, int t, int p) {
	if(f == t) {
		seg[p] = dfnw[f];
		return;
	}
	int m = f + ((t - f) >> 1);
	Build(f, m, p << 1);
	Build(m + 1, t, (p << 1) | 1);
	seg[p] = seg[p << 1] + seg[(p << 1) | 1];
}

void Update(int f, int t, int p) {
	if(f == t && f == l) {
		seg[p] = w;
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

ll Ask(int f, int t) {
	ll sum = 0;
	while(top[f] != top[t]) {
		if(deep[top[f]] > deep[top[t]]) swap(f, t);
		l = id[top[t]], r = id[t];
		sum += Query(1, tot, 1);
		t = father[top[t]];
	}
	if(id[f] > id[t]) swap(f, t);
	l = id[f], r = id[t];
	sum += Query(1, tot, 1) - dfnw[l];
	return sum;
}

void Add() {
	int len = edges.size();
	efrom[l].push_back(len);
	efrom[r].push_back(len);
	edges.push_back(Edge(l, r, w));
}

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

int main() {
	int ch, tmp;
	scanff(n), scanff(q), scanff(s);
	for(int i = 0; i < n - 1; i++) {
		scanff(l), scanff(r), scanff(w);
		Add();
	}

	father[1] = 0;
	sub_size[0] = 0;
	TreeBuild(1, 1);
	TreeDecomposition(1, 0, 1);
	Build(1, tot, 1);

	while(q--) {
		scanff(ch);
		if(ch) {
			scanff(l), scanff(w);
			const Edge& e = edges[l - 1];
			l = deep[e.f] > deep[e.t] ? id[e.f] : id[e.t];
			dfnw[l] = w;
			Update(1, tot, 1);
		}else {
			scanff(r);
			tmp = r;
			printf("%lld\n", Ask(s, r));
			s = tmp;
		}
	}
	return 0;
}
