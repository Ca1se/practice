#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge {
    int f, t, w;
};

const int maxn = 1000 + 5;
int price[maxn];
int ufset[maxn];
int ans;
vector<Edge> edges;

inline int Find(int pos) {
    return (~ufset[pos] ? ufset[pos] = Find(ufset[pos]) : pos);
}

inline void Union(int x, int y, int w) {
    int xx = Find(x);
    int yy = Find(y);
    if(xx == yy) return;
    ans += w;
    ufset[xx] = yy;
}

int main() {
    int t, n, w;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        ans = 0;
        memset(price, 0, (n + 1) * sizeof(int));
        memset(ufset, -1, (n + 1) * sizeof(int));
        edges.clear();
        for(int i = 0; i < n; i++) {
            scanf("%d", price + i);
        }
        for(int i = 0; i < n; i++) {
            for(int k = 0; k < n; k++) {
                scanf("%d", &w);
                if(k > i) {
                    edges.push_back(Edge { i, k, w + price[i] + price[k] });
                }
            }
        }
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });
        for(const auto& it: edges) {
            Union(it.f, it.t, it.w);
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
int to[maxn];
int adaptor[maxn];
bool vis[maxn][maxn];
struct Edge {
    int from, to, dist;
    Edge(int f, int t, int d): from(f), to(t), dist(d) {}
    bool operator< (const Edge& e) const {return dist > e.dist;}
};
int Find(int p) {
    if(to[p] < 0) return p;
    return to[p] = Find(to[p]);
}
void Union(int x, int y) {
    to[x] = y;
}
int main() {
    int t, n, c, ans = 0, cnt = 0;
    priority_queue<Edge> q;
    ios::sync_with_stdio(false);
    cin >> t;
    while(t--) {
        ans = cnt = 0;
        while(!q.empty()) q.pop();
        memset(to, -1, sizeof to); 
        memset(vis, 0, sizeof vis);
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> adaptor[i];
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> c;
                if(i == j || vis[i][j])  continue;
                vis[i][j] = vis[j][i] = true;
                q.emplace(i, j, adaptor[i] + adaptor[j] + c);
            }
        }
        while(!q.empty()) {
            const Edge& e = q.top();
            int i = Find(e.from), j = Find(e.to);
            if(i != j) {
                Union(i, j);
                ans += e.dist;
                cnt++;
            }
            if(cnt == n - 1)    break;
            q.pop();
        }
        cout << ans << endl;
    }
    return 0;
}
*/
