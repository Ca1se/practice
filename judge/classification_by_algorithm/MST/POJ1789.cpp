#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 2000 + 5;
char str[maxn][10];
int to[maxn];
struct Edge {
    Edge(int f, int t, int d): f(f), t(t), d(d) {}
    int f, t, d;
    bool operator< (const Edge& e) const {
        return d > e.d;
    }
};
int Find(int p) {
    if(to[p] < 0)   return p;
    return to[p] = Find(to[p]);
}

int main() {
    int n, ans, cnt;
    while(scanf("%d", &n) != EOF && n) {
        priority_queue<Edge> q;
        ans = cnt = 0;
        memset(to, -1, sizeof to);
        for(int i = 0; i < n; i++) {
            scanf("%s", str[i]);
            for(int j = i - 1; j >= 0; j--) {
                int r = 0;
                for(int k = 0; k < 7; k++) {
                    if(str[i][k] != str[j][k])  r++;
                } 
                q.push(Edge(i, j, r));
            }
        }
        while(!q.empty()) {
            const Edge& t = q.top();
            int i = Find(t.f), j = Find(t.t);
            if(i != j) {
                to[i] = j;
                cnt++;
                ans += t.d;
            }
            if(cnt == n - 1)    break;
            q.pop();
        }
        printf("The highest possible quality is 1/%d.\n", ans);
    }
    return 0;
}
