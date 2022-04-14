#include <cstdio>
#include <map>
#include <utility>
using namespace std;

const int maxm = 1286 + 5;
const int maxn = 128 + 5;

map<int, pair<int, int>> s;
int mp[2][maxm][maxn] = {};
int num = 0, m, n, l, t;

inline int Find(int pos) {
    return s[pos].first ? s[pos].first = Find(s[pos].first) : pos;
}

inline void Union(int x, int y) {
    int rx = Find(x), ry = Find(y);
    if(rx != ry) {
        s[rx].first = ry;
        if(rx == x) {
            int& yc = s[ry].second;
            yc++;
            if(yc == t) num += yc;
            else if(yc > t) num++;
        }else {
            int &xc = s[rx].second, &yc = s[ry].second;
            if(xc >= t && yc < t) num += yc;
            else if(yc >= t && xc < t) num += xc;
            else if(xc < t && xc + yc >= t) num += xc + yc;
            yc += xc;
        }
    }
}

int main() {
    scanf("%d %d %d %d", &m, &n, &l, &t);
    getchar();
    int count, id, nd, np, xpp, ypp, zpp;
    for(int i = 0; i < l; i++) {
        id = i % 2;
        nd = 1 - id;
        for(int k = 1; k <= m; k++) {
            for(int r = 1; r <= n; r++) {
                if((mp[id][k][r] = (getchar() - 48))) {
                    count = 0;
                    np = i * (m * n) + k * n + r;
                    if(mp[id][k - 1][r]) {
                        count++;
                        ypp = np - n;
                        Union(np, ypp);
                    }
                    if(mp[id][k][r - 1]) {
                        count++;
                        xpp = np - 1;
                        Union(np, xpp);
                    }
                    if(mp[nd][k][r]) {
                        count++;
                        zpp = np - (m * n);
                        Union(np, zpp);
                    }
                    if(count == 0) {
                        s[np].second = 1;
                        if(s[np].second == t) num++;
                    }
                }
                getchar();
            }
        }
    }
    printf("%d", num);
    return 0;
}
