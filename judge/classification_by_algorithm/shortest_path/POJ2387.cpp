//注意题目中有没有说有重边， 取小的一个
//朴素实现
/*
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int T, N;
const int maxn = 2000 + 5;
const int INF = 0x3f3f3f3f;
int w[maxn][maxn];
int d[maxn];
bool vis[maxn];
void dijkstra() {
    memset(d, 0x3f3f, sizeof d);
    memset(vis, 0, sizeof vis); 
    d[N] = 0;
    for(int i = 1; i <= N; i++) {
        int x, m = INF;
        for(int j = 1; j <= N; j++) if(!vis[j] && d[j] < m) m = d[x = j];
        vis[x] = 1;
        for(int j = 1; j <= N; j++) d[j] = min(d[j], d[x] + w[x][j]);
    }
    cout << d[1] << endl;
}
int main() {
    memset(w, 0x3f3f, sizeof w);
    cin >> T >> N;
    for(int i = 0; i < T; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        w[u][v] = w[v][u] = min(d, w[u][v]);
    }
    dijkstra(); 
    return 0;
}
*/
//队列优化, 无需考虑重边
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