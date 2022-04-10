#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
const int maxn = 500 + 5;
struct Point {
    Point() = default; 
    Point(int x, int y): x(x), y(y) {}
    double distance(const Point& p) const {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
    int x, y;
}points[maxn];
struct Edge {
    Edge(int f, int t, double d): f(f), t(t), d(d) {}
    int f, t;
    double d;
    bool operator< (const Edge& e) const {
        return d > e.d;
    }
};
int to[maxn];
int Find(int p) {
    if(to[p] < 0)   return p;
    return to[p] = Find(to[p]);
}
int main() {
    int ca, cnt, s, p;
    scanf("%d", &ca); 
    while(ca--) {
        cnt = 0;
        memset(to, -1, sizeof to);
        priority_queue<Edge> q;  
        scanf("%d%d", &s, &p); 
        for(int i = 0; i < p; i++) {
            scanf("%d%d", &points[i].x, &points[i].y);
            for(int j = i - 1; j >= 0; j--) {
                q.push(Edge(i, j, points[i].distance(points[j])));
            }
        }
        while(!q.empty()) {
            const Edge& t = q.top();
            int i = Find(t.f), j = Find(t.t);
            if(i != j) {
                to[i] = j;
                cnt++;
            }
            if(cnt == (p - s)) {
                printf("%.2f\n", t.d);
                break;
            }
            q.pop();
        }
    }
    return 0;
}
