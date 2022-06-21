#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int maxn = 100 + 5;
bool vis[maxn][maxn][5][maxn];
char mp[maxn][maxn];
int t, n, m;
const int path[4][2] = { 1, 0, 0, 1, -1, 0, 0, -1 };

struct S {
    S(int x, int y, int d, int c, int a): x(x), y(y), d(d), c(c), a(a) {}
    int x, y, d, c, a;
};

inline bool check(int x, int y) noexcept {
    return (x >= 0 && x < n && y >= 0 && y < n && mp[y][x] != '*');
}

int main() {
    scanf("%d", &t);
    while(t--) {
        memset(vis, 0, sizeof vis);
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) {
            scanf("%s", mp[i]);
        }

        queue<S> q;
        q.emplace(0, 0, 4, 0, 0);
        while(!q.empty()) {
            const auto& ts = q.front();
            if(ts.x == n - 1 && ts.y == n - 1) {
                printf("%d\n", ts.a);
                goto tend;
            }

            for(int i = 0; i < 4; i++) {
                int xx = ts.x + path[i][0];
                int yy = ts.y + path[i][1];
                if(check(xx, yy)) {
                    if(i == ts.d && ts.c + 1 <= m) {
                        if(!vis[xx][yy][i][ts.c + 1]) {
                            vis[xx][yy][i][ts.c + 1] = true;
                            q.emplace(xx, yy, i, ts.c + 1, ts.a + 1);
                        }
                    }else if(i != ts.d){
                        if(!vis[xx][yy][i][1]) {
                            vis[xx][yy][i][1] = true;
                            q.emplace(xx, yy, i, 1, ts.a + 1);
                        }
                    }
                }
            }

            q.pop();
        }

        printf("-1\n");
tend:
        ;
    }
    return 0;
}
