#include <bits/stdc++.h>
using namespace std;
const int maxn = 4 * 1e4 + 5;
const int inf = 2e9;

struct Edge {
	Edge(int f, int t, int w): f(f), t(t), w(w) {}
	int f, t, w;
};
vector<Edge> edges;
vector<int> efrom[maxn];
int sum, k, rt, cnt, ans, siz[maxn], dist[maxn], maxx[maxn];
int vis[maxn];

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

inline void Add(int x, int y, int w) {
	int len = edges.size();
	efrom[x].push_back(len);
	efrom[y].push_back(len);
	edges.emplace_back(x, y, w);
}

int CalcSize(int r, int fa) {
	siz[r] = 1;
	maxx[r] = 0;

	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == fa || vis[target]) continue;
		siz[r] += CalcSize(target, r);
		maxx[r] = max(maxx[r], siz[target]);
	}
	maxx[r] = max(maxx[r], sum - siz[r]);
	if(maxx[r] < maxx[rt]) rt = r;
	return siz[r];
}

void CalcDist(int r, int fa, int w) {
	dist[++cnt] = w;
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(target == fa || vis[target]) continue;
		CalcDist(target, r, w + e.w);
	}
}

int Calc(int r, int w) {
	cnt = 0;
	CalcDist(r, 0, w);
	sort(dist + 1, dist + cnt + 1);
	int f = 1, t = cnt, res = 0;
	while(f <= t) {
		if(dist[f] + dist[t] <= k) {
			res += (t - f);
			f++;
		}else t--;
	}
	return res;
}

void dfz(int r) {
	ans += Calc(r, 0);
	vis[r] = 1;
	for(int i = 0; i < efrom[r].size(); i++) {
		const auto& e = edges[efrom[r][i]];
		int target = e.f + e.t - r;
		if(vis[target]) continue;
		ans -= Calc(target, e.w);
		sum = siz[target];
		rt = 0;
		CalcSize(target, -1);
		dfz(rt);
	}
}


int main() {
	int n, l, r, w;
	scanff(n);
	for(int i = 0; i < n - 1; i++) {
		scanff(l), scanff(r), scanff(w);
		Add(l, r, w);
	}
	scanff(k);
	rt = 0;
	maxx[0] = inf;
	sum = n;
	CalcSize(1, -1);
	dfz(rt);
	printf("%d\n", ans);
	return 0;
}
