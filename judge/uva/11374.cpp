#include <cstdio>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
const int maxn = 500 + 5;
struct edge {
    edge(int s, int t, int w): s(s), t(t), w(w) {}
    int s, t, w;
};

struct statu {
    statu() = default;
    statu(int uc, int s, int d): uc(uc), s(s), d(d) {}
    int uc, s, d;
    constexpr bool operator > (const statu& other) const {
        return d > other.d;
    }
};

int n, s, e;
int d[2][maxn];
bool vis[2][maxn];
pair<int, int> path[2][maxn];
vector<edge> ed[maxn];
vector<int> ans;
priority_queue<statu, vector<statu>, greater<statu>> q;


int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int m, u, v, w;
    while(~scanf("%d%d%d", &n, &s, &e)) {
        memset(d, 0x3f, sizeof d);
        memset(vis, 0, sizeof vis);
        path[0][s] = { 0, 0 };
        path[1][s] = { 0, 0 };
        for(int i = 0; i < maxn; i++) {
            ed[i].clear();
        }
        ans.clear();
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            ed[u].emplace_back(0, v, w);
            ed[v].emplace_back(0, u, w);
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            ed[u].emplace_back(1, v, w);
            ed[v].emplace_back(1, u, w);
        }

        q.emplace(0, s, 0);
        d[0][s] = 0;
        vis[1][s] = true;

        int used, src, dist;
        while(!q.empty()) {
            const auto& tmp  = q.top();
            used = tmp.uc, src = tmp.s, dist = tmp.d;
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

        if(d[0][e] < d[1][e]) {
            int to = e;
            ans.push_back(e);
            while(path[0][to].second) {
                ans.push_back(path[0][to].second);
                to = path[0][to].second;
            }
            printf("%d", ans.back());
            for(int i = ans.size() - 2; i >= 0; i--) {
                printf(" %d", ans[i]);
            }
            printf("\nTicket Not Used\n");
            printf("%d\n", d[0][e]);
        }else {
            int used = 1, to = e, swi;
            ans.push_back(e);
            while(path[used][to].second) {
                ans.push_back(path[used][to].second);
                if(used == 1 && path[used][to].first == 0)
                    swi = path[used][to].second;
                tie(used, to) = path[used][to];
            }
            printf("%d", ans.back());
            for(int i = ans.size() - 2; i >= 0; i--) {
                printf(" %d", ans[i]);
            }
            printf("\n%d\n", swi);
            printf("%d\n", d[1][e]);
        }

        printf("\n");
    }
    

    return 0;
}
