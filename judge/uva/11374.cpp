#include <cstdio>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
const int maxn = 500 + 5;
struct edge {
    int s, t, w;
};

struct statu {
    int uc, s, d;
    constexpr bool operator < (const statu& other) const {
        return d == other.d ? uc > other. uc : d < other.d;
    }
};

int n, s, e;
int d[2][maxn];
bool vis[2][maxn];
pair<int, int> path[2][maxn];
vector<edge> ed[maxn];


int main() {
    memset(d, 0x3f, sizeof d);
    int m, u, v, w;
    scanf("%d%d%d", &n, &s, &e);
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        ed[u].emplace_back(0, v, w);
        ed[v].emplace_back(0, u, w);
        if(u == s || v == s) {
            d[0][u + v - s] = w;
        }
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        ed[u].emplace_back(1, v, w);
        ed[v].emplace_back(1, u, w);
        if(u == s || v == s) {
            d[1][u + v - s] = w;
        }
    }

    priority_queue<statu, vector<statu>, greater<statu>> q;
    q.emplace(0, s, 0);
    d[0][s] = 0;
    d[1][s] = 0;

    while(!q.empty()) {
        auto [used, src, dist] = q.top();
        q.pop();
        if(vis[used][src]) continue;
        vis[used][src] = true;
        for(int i = 0; i < ed[src].size(); i++) {
            const auto& t = ed[src][i];
            if(t.s == 0) {
                if(d[used][t.t] > dist + t.w) {
                    d[used][t.t] = dist + t.w;
                    path[used][t.t] = { used, src };
                    q.emplace(used, t.t, d[used][t.t]);
                }
            }else if(used == 0) {
                if(d[1][t.t] > dist + t.w) {
                    d[1][t.t] = dist + t.w;
                    path[1][t.t] = { 0, src };
                    q.emplace(1, t.t, d[1][t.t]);
                }
            }
        }
    }
    vector<int> ans;

    if(d[0][e] < d[1][e]) {
        int to = e;
        ans.push_back(e);
        while(path[0][to].second) {
            ans.push_back(path[0][to].second);
            to = path[0][to].second;
        }
    }else {
        int used = 1, to = e;
        ans.push_back(e);
        while(path[used][to].second) {
            ans.push_back(path[used][to].second);
            int u = used;
            used = path[used][to].first;
            to = path[u][to].second;
        }
    }



    return 0;
}
