#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
const int inf = 0x3f3f3f3f;
bool block[maxn][maxn], vis[maxn][maxn][1005];
vector<int> xc[maxn], yc[maxn];
int m, n, k, d, t, v, x, y;
int cxy[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char dir;

struct Castle {
	Castle(char dir, int t, int v, int x, int y): dir(dir), t(t), v(v), x(x), y(y) {}
	char dir;
	int t, v, x, y;
};
vector<Castle> cs;

struct S {
	S(int x, int y, int pre, int time): x(x), y(y), pre(pre), time(time) {}
	int x, y, pre, time;
};

bool ok(int x, int y, int pre, int i, int t) {
	if(x < 0 || x > m || y < 0 || y > n) return false;
	if(block[y][x] || vis[y][x][t] || (pre % 2 == i % 2 && i != pre) || (t == d && (x != m || y != n))) return false;
	int x1, x2;
	int dx1 = inf, dx2 = inf;
	for(int i = 0; i < yc[y].size(); i++) {
		int dx = abs(cs[yc[y][i]].x - x);
		if(dx1 > dx) {
			dx2 = dx1;
			dx1 = dx;
			x2 = x1;
			x1 = yc[y][i];
		}else if(dx2 > dx) {
			dx2 = dx;
			x2 = yc[y][i];
		}
	}
	const auto* c1 = &cs[x1];
	const auto* c2 = &cs[x2];
	if(dx1 != inf && ((c1->x > x && c1->dir == 'W') || (c1->x < x && c1->dir == 'E')) && abs(c1->x - x) % c1->v == 0) {
		if(abs(c1->x - x) / c1->v <= t && (t - abs(c1->x - x) / c1->v) % c1->t == 0) return false;
	}
	if(dx2 != inf && ((c1->x - x) * (c2->x - x) < 0) && ((c2->x > x && c2->dir == 'W') || (c2->x < x && c2->dir == 'E')) && abs(c2->x - x) % c2->v == 0) {
		if(abs(c2->x - x) / c2->v <= t && (t - abs(c2->x - x) / c2->v) % c2->t == 0) return false;
	}
	int y1, y2;
	int dy1 = inf, dy2 = inf;
	for(int i = 0; i < xc[x].size(); i++) {
		int dy = abs(cs[xc[x][i]].y - y);
		if(dy1 > dy) {
			dy2 = dy1;
			dy1 = dy;
			y2 = y1;
			y1 = xc[x][i];
		}else if(dy2 > dy) {
			dy2 = dy;
			y2 = xc[x][i];
		}
	}
	c1 = &cs[y1], c2 = &cs[y2];	
	if(dy1 != inf && ((c1->y > y && c1->dir == 'N') || (c1->y < y && c1->dir == 'S')) && abs(c1->y - y) % c1->v == 0) {
		if(abs(c1->y - y) / c1->v <= t && (t - abs(c1->y - y) / c1->v) % c1->t == 0) return false;
	}
	if(dy2 != inf && ((c1->y - y) * (c2->y - y) < 0) && ((c2->y > y && c2->dir == 'N') || (c2->y < y && c2->dir == 'S')) && abs(c2->y - y) % c2->v == 0) {
		if(abs(c2->y - y) / c2->v <= t && (t - abs(c2->y - y) / c2->v) % c2->t == 0) return false;
	}
	return true;
}

int bfs() {
	queue<S> q;
	q.emplace(0, 0, -1, 0);
	vis[0][0][0] = true;
	while(!q.empty()) {
		const auto& it = q.front();
		int cnt = 0;
		for(int i = 0; i < 4; i++) {
			int x = it.x + cxy[i][0], y = it.y + cxy[i][1];
			if(ok(x, y, it.pre, i, it.time + 1)) {
				if(x == m && y == n) return it.time + 1;
				vis[y][x][it.time + 1] = true;
				q.emplace(x, y, i, it.time + 1);
			}else cnt++;
		}
		if(cnt == 4 && ok(it.x, it.y, -1, -1, it.time + 1))
			q.emplace(it.x, it.y, -1, it.time + 1);
		q.pop();
	}
	return -1;
}

int main() {
	while(~scanf("%d%d%d%d", &n, &m, &k, &d)) {
		memset(block, 0, sizeof block);
		memset(vis, 0, sizeof vis);
		cs.clear();
		for(int i = 0; i <= 100; i++) {
			xc[i].clear();
			yc[i].clear();
		}
		while(k--) {
			scanf(" %c%d%d%d%d", &dir, &t, &v, &y, &x);
			int len = cs.size();
			xc[x].push_back(len);
			yc[y].push_back(len);
			cs.emplace_back(dir, t, v, x, y);
			block[y][x] = true;
		}
		int j = bfs();
		if(j != -1) printf("%d\n", j);
		else printf("Bad luck!\n");
	}
	return 0;
}
