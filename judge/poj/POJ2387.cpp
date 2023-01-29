/*
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 2000 + 5;
const int INF = 0x3f3f3f3f;

int T, N;
struct Edge {
    int from, to, dist;
    Edge(int from, int to, int dist): from(from), to(to), dist(dist) {}
};

struct Dijkstra {
    vector<Edge> edges;
    vector<int> G[maxn];    
    bool vis[maxn];
    int d[maxn];

    void add_edge(int from, int to, int dist) {
        G[from].push_back(edges.size());
        edges.push_back(Edge(from, to, dist));
    }

    void dijkstra() {
        memset(vis, 0, sizeof vis);
        memset(d, 0x3f3f, sizeof d);
        d[N] = 0;

        typedef pair<int, int> pii;
        priority_queue<pii, vector<pii>, greater<pii> > q;
        q.push(make_pair(0, N));

        while(!q.empty()) {
            pii t = q.top(); q.pop();
            if(vis[t.second])   continue;
            vis[t.second] = 1;
            
            for(int i = 0; i < G[t.second].size(); i++) {
                Edge& it = edges[G[t.second][i]];
                if(d[it.to] > d[t.second] + it.dist) {
                    d[it.to] = d[t.second] + it.dist;
                    q.push(make_pair(d[it.to], it.to));
                }
            }
        }
        cout << d[1] << endl;
    }
};

int main() {
    cin >> T >> N;
    Dijkstra d;
    for(int i = 0; i < T; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        d.add_edge(u, v, w);
        d.add_edge(v, u, w); 
    }
    d.dijkstra();
}
*/

#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

struct Edge
{
    Edge(int to, int len): to(to), len(len) {}
    int to, len;
};

static const int maxn = 1000 + 5;
int dist[maxn];
struct Step
{
    Step(int pos): pos(pos) {}
    int pos;
    bool operator<(const Step& s) const
    {
        return dist[this->pos] > dist[s.pos];
    }
};

int t, n;
std::vector<Edge> edges[maxn];
std::priority_queue<Step> q;

int main() {
    int x, y, c;
    memset(dist, 0x3f, sizeof dist);
    scanf("%d%d", &t, &n);
    for(int i = 0; i < t; i++) {
        scanf("%d%d%d", &x, &y, &c);
        edges[x].push_back(Edge(y, c));
        edges[y].push_back(Edge(x, c));
    }
    q.push(Step(n));
    dist[n] = 0;
    while(!q.empty()) {
        Step now = q.top();
        q.pop();
        if(now.pos == 1) {
            printf("%d\n", dist[1]);
            break;
        }
        const std::vector<Edge>& es = edges[now.pos];
        for(int i = 0; i < es.size(); i++) {
            const Edge& e = es[i];
            if(dist[e.to] > dist[now.pos] + e.len) {
                dist[e.to] = dist[now.pos] + e.len;
                q.push(e.to);
            }
        }
    }
    return 0;
}


