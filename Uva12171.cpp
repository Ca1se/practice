#include<bits/stdc++.h>
using namespace std;

struct Point {
    Point(int x, int y, int z): x(x), y(y), z(z) {}
    Point() = default;
    int x, y, z;
    Point operator+ (const Point p) const {
        Point t;
        t.x = x + p.x;
        t.y = y + p.y;
        t.z = z + p.z;
        return t;
    }
};

const int maxn = 100 + 5;
const int maxr = 1000 + 5;
const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};
int dicar[maxn][maxn][maxn], vis[maxn][maxn][maxn], x[maxn], y[maxn], z[maxn], n, v, s, nx, ny, nz;
Point p[maxn];

void solve() {
    queue<Point> q;
    q.push(Point(0, 0, 0));
    vis[0][0][0] = 1;

    while(!q.empty()){
        Point t = q.front(); q.pop();
        v += (x[t.x + 1] - x[t.x]) * (x[t.y + 1] - y[t.y]) * (z[t.z + 1] - z[t.z]);
        for(int i = 0; i < 6; i++){
            int xx = t.x + dx[i];
            int yy = t.y + dy[i];
            int zz = t.z + dz[i];
            if(xx < 0 || xx > nx - 1 || yy < 0 || yy > ny - 1 || zz < 0 || zz > nz -1 || vis[xx][yy][zz])  continue;
            else if(dicar[xx][yy][zz]){
                //--
                s++;
                continue;
            }
            vis[xx][yy][zz] = 1;
            q.push(Point(xx, yy, zz));
        }
    }
}

int main() {
    int test;
    cin >> test;
    while(test--){
        memset(dicar, 0, sizeof(dicar));
        memset(vis, 0, sizeof(vis));
        v = 0, s = 0;
        cin >> n;
        for(int i = 1; i <= 2 * n; i += 2){
            cin >> p[i].x >> p[i].y >> p[i].z >> p[i + 1].x >> p[i + 1].y >> p[i + 1].z;
            p[i + 1] = p[i] + p[i + 1];
            x[i] = p[i].x, y[i] = p[i].y, z[i] = p[i].z;
            x[i + 1] = p[i + 1].x, y[i + 1] = p[i + 1].y, z[i + 1] = p[i + 1].z;
        }
        x[0] = 0, y[0] = 0, z[0] = 0;

        sort(x, x + 2 * n + 1);
        sort(y, y + 2 * n + 1);
        sort(z, z + 2 * n + 1);

        nx = unique(x, x + 2 * n + 1) - x;
        ny = unique(y, y + 2 * n + 1) - y;
        nz = unique(z, z + 2 * n + 1) - z;

        x[nx++] = maxr; y[ny++] = maxr; z[nz++] = maxr;

        for(int i = 1; i <= 2 * n; i += 2){
            int x1, y1, z1, x2, y2, z2;
            x1 = lower_bound(x, x + nx, p[i].x) - x;
            y1 = lower_bound(y, y + ny, p[i].y) - y;
            z1 = lower_bound(z, z + nz, p[i].z) - z;
            x2 = lower_bound(x, x + nx, p[i + 1].x) - x;
            y2 = lower_bound(y, y + ny, p[i + 1].y) - y;
            z2 = lower_bound(z, z + nz, p[i + 1].z) - z;

            for(int r = x1; r < x2; r++){
                for(int g = y1; g < y2; g++){
                    for(int b = z1; b < z2; b++){
                        dicar[r][g][b] = 1;
                    }
                }
            }
        }
        solve();
        cout << v << ' ' << s << endl;
    }
    return 0;
}