#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct Edge {
    int from, to, dist;
    Edge(int f, int t, int w): from(f), to(t), dist(w) {}
    bool operator< (const Edge& e) const {
        return dist > e.dist;
    }
};
const int maxn = 26;
int to[maxn + 5];

int Find(int p) {
    if(to[p] < 0)   return p;
    return to[p] = Find(to[p]);
}

void Union(int x, int y) {
    to[x] = y;
}

int main() {
    int n, ans;
    priority_queue<Edge> q;
    while(cin >> n && n) {
        ans = 0;
        memset(to, -1, sizeof to);
        for(int i = 0; i < n - 1; i++) {
            char ch, ch1; int t, w;
            cin >> ch >> t;
            while(t--) {
                cin >> ch1 >> w;
                q.push(Edge(ch - 'A', ch1 - 'A', w));
            }
        }
        while(!q.empty()) {
            const Edge& t = q.top();
            int i = Find(t.from), j = Find(t.to);
            if(i != j) {
                Union(i, j);
                ans += t.dist;
            }
            q.pop();
        }
        cout << ans << endl;
    }
    return 0;
}
