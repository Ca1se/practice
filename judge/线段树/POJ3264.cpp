#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 50000 + 5;
int mind[maxn << 2] = {0};
int maxd[maxn << 2] = {0};
int a[maxn];
int minn, maxx;
void build(int s, int t, int p) {
    if(s == t) {
        mind[p] = a[s];
        maxd[p] = a[s];
        return; 
    }
    int m = (s + t) >> 1;
    if(s <= m)  build(s, m, p << 1);
    if(m < t)   build(m + 1, t, (p << 1) | 1);
    mind[p] = min(mind[p << 1], mind[(p << 1) | 1]);
    maxd[p] = max(maxd[p << 1], maxd[(p << 1) | 1]);
}

void get(int l, int r, int s, int t, int p) {
    if(l <= s && t <= r) {
        maxx = max(maxx, maxd[p]);
        minn = min(minn, mind[p]);
        return;
    }
    int m = (s + t) >> 1;
    if(l <= m)  get(l, r, s, m, p << 1);
    if(m < r)   get(l, r, m + 1, t, (p << 1) | 1);
}
int main() {
    ios::sync_with_stdio(false);
    int n, q, l, r;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, n, 1);
    while(q--) {
        maxx = 0, minn = 0x3f3f3f3f;
        cin >> l >> r;
        get(l, r, 1, n, 1);
        cout << maxx - minn << endl;
    }
    return 0;
}
