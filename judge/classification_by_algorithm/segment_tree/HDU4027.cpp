#include <bits/stdc++.h>
#define  ll long long
using namespace std;
const int maxn = 100000 + 5;
ll a[maxn];
ll d[maxn << 2] = {0};
void build(int s, int t, int p) {
    if(s == t) {
        d[p] = a[s];
        return; 
    }
    int m = (s + t) >> 1;
    if(s <= m)  build(s, m, p << 1);
    if(m < t)   build(m + 1, t, (p << 1) | 1);
    d[p] = d[p << 1] + d[(p << 1) | 1];
}
void update(int l, int r, int s, int t, int p) {
    if(l <= s && t <= r && (t - s + 1) == d[p]) {
        return;
    }else if(s == t) {
        d[p] = sqrt(d[p]);
        return;
    }
    int m = (s + t) >> 1;
    if(l <= m)  update(l, r, s, m, p << 1);
    if(m < r)   update(l, r, m + 1, t, (p << 1) | 1);
    d[p] = d[p << 1] + d[(p << 1) | 1];
}
ll getSum(int l, int r, int s, int t, int p) {
    if(l <= s && t <= r) {
        return d[p];
    }
    ll m = (s + t) >> 1, sum = 0;
    if(l <= m)  sum += getSum(l, r, s, m, p << 1);
    if(m < r)   sum += getSum(l, r, m + 1, t, (p << 1) | 1);
    return sum;
}
int main() {
    ios::sync_with_stdio(false);
    int n, m, c, l, r, cnt = 0;
    while(cin >> n) {
        cout << "Case #" << ++cnt << ":\n";
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        } 
        build(1, n, 1);
        cin >> m;
        while(m--) {
            cin >> c >> l >> r;
            if(c == 0) {
                update(min(l, r), max(l, r), 1, n, 1);
            }else {
                cout << getSum(min(l, r), max(l, r), 1, n, 1) << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
