#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
struct Edge {
    int from, to, dist;   
    Edge(int f, int t, int d): from(f), to(t), dist(d) {}
    bool operator< (const Edge& e) const {
        return dist > e.dist;
    }
};
const int maxn = 50 + 5;
const int maxm = 100 + 5;
int to[maxn];

inline int Find(int p) {
    if(to[p] < 0)   return p;
    return to[p] = Find(to[p]);
}

inline void Union(int x, int y) {
    to[x] = y;
}

int main() {
    int n, m, f, t, d, ans;
    priority_queue<Edge> q;
    while(cin >> n && n) {
        ans = 0;
        memset(to, -1, sizeof to);
        cin >> m;
        while(m--) {
            cin >> f >> t >> d;
            q.push(Edge(f, t, d));
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