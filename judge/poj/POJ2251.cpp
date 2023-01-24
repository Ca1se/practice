/*
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct Point {
    Point(int x, int y, int z, int step): x(x), y(y), z(z), step(step) {}
    int x, y, z, step;
};
const int maxn = 30 + 5;
const int dire[6][3] = {1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1};
char dungeon[maxn][maxn][maxn];
bool vis[32000];
int L, R, C;
bool inrange(int x, int y, int z) {
    return x >= 0 && x < R && y >= 0 && y < C && z >= 0 && z < L;
}
void bfs(int x, int y, int z) {
    queue<Point> q;
    q.push(Point(x, y, z, 0));
    while(!q.empty()){
        Point t = q.front(); q.pop();
        if(dungeon[t.z][t.x][t.y] == 'E'){
            cout << "Escaped in " << t.step << " minute(s).\n";
            return;
        }
        for(int i = 0; i < 6; i++){
            int xx = t.x + dire[i][0], yy = t.y + dire[i][1], zz = t.z + dire[i][2], wh = (zz << 10) | (xx << 5) | yy;
            if(inrange(xx, yy, zz) && dungeon[zz][xx][yy] != '#' && !vis[wh]){
                vis[wh] = true;
                q.push(Point(xx, yy, zz, t.step + 1));
            }
        }
    }
    cout << "Trapped!\n";
}
int main() {
    ios::sync_with_stdio(false);
    int x, y, z;
    while(cin >> L >> R >> C && (L || R || C)){
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < L; i++){
            for(int j = 0; j < R; j++){
                for(int k = 0; k < C; k++){
                    cin >> dungeon[i][j][k];
                    if(dungeon[i][j][k] == 'S'){
                        z = i, x = j, y = k;
                    }
                }
            }
        }
        bfs(x, y, z);
    }
    return 0;
}
*/


#include <cstdio>
#include <queue>
#include <cstring>


static const int maxn = 30 + 5;
int l, r, c;
char mp[maxn][maxn][maxn];
bool visit[maxn][maxn][maxn];
static const int step[6][3] = {
    1, 0, 0,
    -1, 0, 0,
    0, 1, 0,
    0, -1, 0,
    0, 0, 1,
    0, 0, -1
};


struct Status
{
    Status(int l, int r, int c, int cnt): l(l), r(r), c(c), cnt(cnt) {}
    int l, r, c;
    int cnt;
};

inline bool check(int nl, int nr, int nc)
{
    return ((nl >= 0 && nl < l) && (nr >= 0 && nr < r) && (nc >= 0 && nc < c) && (visit[nl][nr][nc] == false) && (mp[nl][nr][nc] != '#'));
}

int main() {
    while(true) {
        memset(visit, 0, sizeof visit);
        std::queue<Status> q;
        scanf("%d%d%d", &l, &r, &c);
        getchar();
        if(l == 0 || r == 0 || c == 0)
            break;
        for(int i = 0; i < l; i++) {
            for(int j = 0; j < r; j++) {
                for(int k = 0; k < c; k++) {
                    scanf("%c", &mp[i][j][k]);
                    if(mp[i][j][k] == 'S') {
                        q.push(Status( i, j, k, 0 ));
                        visit[i][j][k] = true;
                    }
                }
                getchar();
            }
            getchar();
        }
        bool jud = false;
        while(!q.empty()) {
            const Status& now = q.front();
            for(int i = 0; i < 6; i++) {
                int nl = now.l + step[i][0];
                int nr = now.r + step[i][1];
                int nc = now.c + step[i][2];
                if(check(nl, nr, nc)) {
                    if(mp[nl][nr][nc] == 'E') {
                        printf("Escaped in %d minute(s).\n", now.cnt + 1);
                        jud = true;
                        goto ok;
                    }else {
                        q.push(Status( nl, nr, nc, now.cnt + 1 ));
                        visit[nl][nr][nc] = true;
                    }
                }
            }
            q.pop();
        }
        printf("Trapped!\n");
ok:;
    }
    return 0;
}


