#include<cstdio>
#include<queue>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn = 100 + 5;
int to[maxn];
struct Cell {
    double x, y, z, r;
}cells[maxn];
struct Edge {
    int from, to;
    double dist;
    Edge(int f, int t, double d): from(f), to(t), dist(d) {}
    bool operator< (const Edge& e) const {
        return dist > e.dist; 
    }
};
double Distance(const Cell& lhs, const Cell& rhs) {
    return sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y) 
            + (lhs.z - rhs.z) * (lhs.z - rhs.z)) - lhs.r - rhs.r;
}
int Find(int p) {
    if(to[p] < 0)   return p;
    return to[p] = Find(to[p]);
}
void Union(int x, int y) {
    to[x] = y;
}
int main() {
    int n;
    priority_queue<Edge> q;
    while(scanf("%d", &n) != EOF && n) {
        int cnt = 0;
        double ans = 0;
        memset(to, -1, sizeof to);
        while(!q.empty()) {q.pop();}
        for(int i = 0; i < n; i++) {
            Cell& t = cells[i];
            scanf("%lf%lf%lf%lf", &t.x, &t.y, &t.z, &t.r);
            for(int j = i - 1; j >= 0; j--) {
                q.push(Edge(i, j, Distance(t, cells[j])));
            }
        }
        while(!q.empty()) {
            const Edge& t = q.top(); 
            int i = Find(t.from), j = Find(t.to);
            if(i != j) {
                Union(i , j);
                if(t.dist > 0)  ans += t.dist;
                cnt++;
            }
            if(cnt == n - 1)    break;
            q.pop();
        }
        printf("%.3lf\n", ans); 
    }
    return 0;
}
