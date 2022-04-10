#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
int d[maxn << 2] = {0}, lazy[maxn << 2] = {0};
void checkLazy(int s, int t, int m, int p) {
    if(lazy[p] && s != t) {
        d[p << 1] = (m - s + 1) * lazy[p];
        d[(p << 1) | 1] = (t - m) * lazy[p];
        lazy[p << 1] = lazy[(p << 1) | 1] = lazy[p];
        lazy[p] = 0;
    }
}
void update(int l, int r, int v, int s, int t, int p) {
    if(l <= s && t <= r) {
        d[p] = v * (t - s + 1);
        lazy[p] = v;
        return;
    }
    int m = (s + t) >> 1;
    checkLazy(s, t, m, p);
    if(l <= m)  update(l, r, v, s, m, p << 1);
    if(m < r)   update(l, r, v, m + 1, t, (p << 1) | 1);
    d[p] = d[p << 1] + d[(p << 1) | 1];
}
int main() {
    ios::sync_with_stdio(false);
    int c, n = 0, m, l, r, v, cnt = 0;
    cin >> c;
    while(c--) {
        memset(d, 0, sizeof(int) * (n << 2));
        memset(lazy, 0, sizeof(int) * (n << 2));
        cin >> n >> m;
        update(1, n, 1, 1, n, 1);
        while(m--) {
            cin >> l >> r >> v;
            update(l, r, v, 1, n, 1);
        } 
        cout << "Case " << ++cnt << ": The total value of the hook is " << d[1] << ".\n";
    }
    return 0;
}
