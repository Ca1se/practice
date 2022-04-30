#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 100 + 5;
int to[maxn];
struct Edge {
    Edge(int f, int t, int d): from(f), to(t), dist(d) {}
    int from, to, dist;
    bool operator< (const Edge& e) const {
        return dist > e.dist;
    }
};
int Find(int p) {
    if(to[p] < 0)   return p;
    return to[p] = Find(to[p]);
}
void Union(int x, int y) {
    to[x] = y;
}
int main() {
    int n, d, ans = 0, cnt = 0;
    memset(to, -1, sizeof to);
    cin >> n;
    priority_queue<Edge> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> d;
            if(i == j)  continue;
            q.push(Edge(i, j, d));
        }
    }
    int m;
    cin >> m;
    int i, j;
    while(m--) {
        cin >> i >> j;
        q.push(Edge(i - 1, j - 1, 0));
    }
    while(!q.empty()) {
        const Edge& t = q.top();
        int i = Find(t.from), j = Find(t.to);
        if(i != j) {
            Union(i, j);
            ans += t.dist; 
            cnt++;
        }
        if(cnt == n - 1)    break;
        q.pop();
    }
    cout << ans << endl;
    return 0;
}
