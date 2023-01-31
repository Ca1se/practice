#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>


struct Edge
{
    Edge(int to, int weight): to(to), weight(weight) {}
    int to, weight;
};

static const int maxn = 1000 + 5;
int n, m;
bool vis[maxn];
std::vector<Edge> edges[maxn];

bool bfs(int weight) {
    memset(vis, 0, sizeof vis);
    std::queue<int> q;
    q.push(1);
    vis[1] = true;
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        const std::vector<Edge>& es = edges[now];
        for(int i = 0; i < es.size(); i++) {
            Edge e = es[i];
            if(!vis[e.to] && weight <= e.weight) {
                if(e.to == n) return true;
                q.push(e.to);
                vis[e.to] = true;
            }
        }
    }

    return false;
}

int main() {
    int t, cnt = 0;
    int x, y, w;
    scanf("%d", &t);
    while(t--) {
        for(int i = 0; i < maxn; i++)
            edges[i].clear();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &w);
            edges[x].push_back(Edge(y, w));
            edges[y].push_back(Edge(x, w));
        }
        int left = 0, right = 1000000;
        while(left != right) {
            int now = (left + right + 1) >> 1;
            if(bfs(now))
                left = now;
            else
                right = now - 1;
        }
        printf("Scenario #%d:\n%d\n\n", ++cnt, left);
    }

    return 0;
}
