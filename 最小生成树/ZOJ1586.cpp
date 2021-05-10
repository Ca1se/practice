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
