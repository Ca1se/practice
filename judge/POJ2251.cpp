#include<queue>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 30 + 5;
char mp[maxn][maxn][maxn] = {0};
bool vis[maxn][maxn][maxn] = {0};
int m, n, h;
const int dir[6][3] = {1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1};
namespace solve {
    struct Point {
        Point() = default;
        Point(int x, int y, int z): x(x), y(y), z(z) {}
        int x, y, z;

        bool operator== (const Point& t) const {
            return (x == t.x && y == t.y && z == t.z);
        }
    }start, end;
}
void sol() {
    queue<pair<solve::Point, int> > q;
    q.push(make_pair(solve::start, 0));

    while(!q.empty()){
        pair<solve::Point, int> t = q.front();
        q.pop();

        if(t.first == solve::end){
            cout << "Escaped in " << t.second << " minute(s)." << endl;
            return;
        }
        for(int i = 0; i < 6; i++){
            solve::Point r(t.first.x + dir[i][0], t.first.y + dir[i][1], t.first.z + dir[i][2]);
            if(r.x < n && r.y < m && r.z < h && r.x >= 0 && r.y >= 0 && r.z >= 0 && !vis[r.z][r.y][r.x] && mp[r.z][r.y][r.x] != '#'){
                q.push(make_pair(r, t.second + 1));
                vis[r.z][r.y][r.x] = true;
            }
        }
    }
    cout << "Trapped!" << endl;
}
int main() {
    ios::sync_with_stdio(false);
    while(cin >> h >> m >> n && (h || m || n)){
        memset(mp, 0, sizeof(mp));
        memset(vis, 0, sizeof(vis));
        for(int k = 0; k < h; k++){
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    cin >> mp[k][i][j];
                    if(mp[k][i][j] == 'S'){
                        solve::start = solve::Point(j, i, k);
                    }else if(mp[k][i][j] == 'E'){
                        solve::end = solve::Point(j, i, k);
                    }
                }
            }
        }
        sol();
    }
    return 0;
}