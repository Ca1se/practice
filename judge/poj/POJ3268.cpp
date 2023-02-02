#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

struct Edge
{
    Edge(int to, int len): to(to), len(len) {}
    int to, len;
};

struct Status
{
    Status(int pos, int dist): pos(pos), dist(dist) {}
    int pos, dist;
    bool operator<(const Status& other) const
    {
        return this->dist > other.dist;
    }
};

static const int maxn = 1000 + 5;
int n, m, x, ans = -1;
int dist[maxn];
int dist1[maxn];
std::vector<Edge> edges[maxn];

inline void solve(int s)
{
    std::priority_queue<Status> q;
    q.push(Status(s, 0));
    dist[s] = 0;
    while(!q.empty()) {
        Status now = q.top();
        q.pop();
        for(int i = 0; i < edges[now.pos].size(); i++) {
            Edge e = edges[now.pos][i];
            if(dist[e.to] > now.dist + e.len) {
                dist[e.to] = now.dist + e.len;
                q.push(Status(e.to, dist[e.to]));
            }
        }
    }
}

inline void solve1(int s)
{
    memset(dist1, 0x3f, sizeof dist1);
    std::priority_queue<Status> q;
    q.push(Status(s, 0));
    dist1[s] = 0;
    while(!q.empty()) {
        Status now = q.top();
        q.pop();
        if(now.pos == x) {
            ans = std::max(ans, dist[s] + now.dist);
            return;
        }
        for(int i = 0; i < edges[now.pos].size(); i++) {
            Edge e = edges[now.pos][i];
            if(dist1[e.to] > now.dist + e.len) {
                dist1[e.to] = now.dist + e.len;
                q.push(Status(e.to, dist1[e.to]));
            }
        }
    }
}

int main() {
    memset(dist, 0x3f, sizeof dist);
    int a, b, d;
    scanf("%d%d%d", &n, &m, &x);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &d);
        edges[a].push_back(Edge(b, d));
    }
    solve(x);
    for(int i = 1; i <= n; i++) {
        if(i == x) continue;
        solve1(i);
    }
    printf("%d\n", ans);
    return 0;
}