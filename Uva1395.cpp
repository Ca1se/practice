#include<iostream>
#include<algorithm>
#include<set>
//#define LOCAL
using namespace std;
const int maxm = 100 * 99 / 2;
const int INF = 0x3f3f3f3f;
int u[maxm], v[maxm], w[maxm], r[maxm], p[100 + 5], n, m, ans;

int _find(int s) {
    return p[s] == s ? s : p[s] = _find(p[s]);
}

bool cmp(int x, int y) {
    return w[x] < w[y];
}

bool solve() {
    for (int i = 0; i < m; i++)  r[i] = i;
    sort(r, r + m, cmp);
    for (int i = 0; i < m; i++) {
        int maxx, minn, cnt = 0;
        maxx = minn = w[r[i]];
        for (int j = 0; j < n + 1; j++)  p[j] = j;
        for (int j = i; j < m; j++) {
            int e = r[j];   int x = _find(u[e]);   int y = _find(v[e]);
            if (x != y) {
                cnt++;
                p[x] = y;
                maxx = max(maxx, w[e]);
            }
            if (cnt == n - 1) {
                ans = min(ans, maxx - minn);
                break;
            }
        }
    }
    return ans == INF ? false : true;
}

int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    freopen("test.out", "w+", stdout);
#endif
    while (cin >> n >> m && n) {
        ans = INF;
        for (int i = 0; i < m; i++) {
            cin >> u[i] >> v[i] >> w[i];
        }
        if (solve()) {
            cout << ans << endl;
        }
        else {
            cout << -1 << endl;
        }
    }
    return 0;
}