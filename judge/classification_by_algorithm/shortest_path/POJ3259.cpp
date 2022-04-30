#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 500 + 5;
struct Edge {
    Edge() {};
    Edge(int t, int w): t(t), w(w) {}
    int t, w;
};

vector<Edge> edges[maxn];
int cnt[maxn];
int dist[maxn];
bool vis[maxn];
queue<int> q;

int main() {
    int t, n, m, w, from, to, weight;
    bool flag;
    scanf("%d", &t);
    while(t--) {
        for(int i = 0; i < maxn; i++) edges[i].clear();
        while(!q.empty()) q.pop();
        memset(vis, 0, sizeof vis);
        memset(cnt, 0, sizeof cnt);
        memset(dist, 0x3f, sizeof dist);
        scanf("%d%d%d", &n, &m, &w);
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &from, &to, &weight);
            edges[from].push_back(Edge(to, weight));
            edges[to].push_back(Edge(from, weight));
        }
        for(int i = 0; i < w; i++) {
            scanf("%d%d%d", &from, &to, &weight);
            edges[from].push_back(Edge(to, -weight));
        }
        for(int i = 1; i <= n; i++) {
            edges[0].push_back(Edge(i, 0));
        }
        q.push(0);
        vis[0] = true;
        dist[0] = 0;
        flag = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = false;
            for(int i = 0; i < edges[u].size(); i++) {
                int v = edges[u][i].t, w = edges[u][i].w;
                if(dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    cnt[v] = cnt[u] + 1;
                    if(cnt[v] > n) {
                        flag = false;
                        goto e;
                    }
                    if(!vis[v]) q.push(v), vis[v] = true;
                }
            }
        }
e:
        if(!flag) {
            puts("YES");
        }else {
            puts("NO");
        }
    }
    return 0;
}
