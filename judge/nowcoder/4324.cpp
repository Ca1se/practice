#include <cstdio>
#include <cstring>
#include <iterator>
#include <stack>
using namespace std;

const int maxn = 500 + 5;
int mp[maxn][maxn] = {};
int has[maxn] = {};
int need[maxn] = {};
int had[maxn] = {};
bool vis[maxn] = {};
int path[maxn] = {};

int main() {
    memset(mp, 0x3f3f3f3f, sizeof mp);
    memset(need, 0x3f3f3f3f, sizeof need);
    memset(path, -1, sizeof path);
    int cm, n, sp, m;
    scanf("%d %d %d %d", &cm, &n, &sp, &m);
    cm = cm / 2;
    for(int i = 1; i < n + 1; i++) {
        scanf("%d", has + i);
    }
    int x, y, tr;
    for(int i = 0; i < m; i++) {
        scanf("%d %d",&x, &y);
        scanf("%d", &tr);
        mp[y][x] = mp[x][y] = std::min(tr, mp[x][y]);
        if(x == 0 || y == 0) {
            int tmp = x + y;
            need[tmp] = cm - has[tmp];
            if(need[tmp] < 0) {
                had[tmp] = -need[tmp];
                need[tmp] = 0;
            }
            path[x + y] = 0;
        }
    }
    path[0] = -1;

    for(int i = 0; i < n; i++) {
        int minp = 0x3f3f3f3f, minn = 0x3f3f3f3f, maxh = -1, ind;
        for(int k = 1; k < n + 1; k++) {
            if(!vis[k] && (mp[0][k] < minp || (mp[0][k] == minp && (need[k] < minn || (need[k] == minn && had[k] > maxh)))))
                ind = k, minp = mp[0][k], minn = need[k], maxh = had[k];
        }
        if(ind == sp) {
            std::stack<int> m;
            for(int r = sp; ~r; r = path[r]) {
                m.push(r);
            }
            printf("%d %d", need[sp], m.top());
            m.pop();
            while(!m.empty()) {
                printf("->%d", m.top());
                m.pop();
            }
            printf(" %d", had[sp]);
            return 0;
        }
        vis[ind] = true;
        for(int k = 1; k < n + 1; k++) {
            int dist = mp[0][ind] + mp[ind][k];
            if((dist < mp[0][k]) || (dist == mp[0][k] && (std::max(cm - had[ind] - has[k], 0) + need[ind]) < need[k])) {
                mp[0][k] = mp[k][0] = dist;
                need[k] = std::max(cm - had[ind] - has[k], 0) + need[ind];
                had[k] = std::max(had[ind] + has[k] - cm, 0);
                path[k] = ind;
            }
        }
    }

    return 0;
}
