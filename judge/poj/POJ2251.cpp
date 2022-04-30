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