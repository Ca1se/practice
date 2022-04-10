#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int maxn = 100000 + 5;
ll a[maxn];
ll d[maxn << 2] = {0};
ll lazy[maxn << 2] = {0};
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
void checkLazy(int s, int t, int m, int p) {
    if(lazy[p] && s != t) {
        d[p << 1] += (m - s + 1) * lazy[p];
        d[(p << 1) | 1] += (t - m) * lazy[p];
        lazy[p << 1] += lazy[p];
        lazy[(p << 1) | 1] += lazy[p];
        lazy[p] = 0;
    }
}
ll getSum(int l, int r, int s, int t, int p) {
    if(l <= s && t <= r) {
        return d[p];
    } 
    ll m = (s + t) >> 1, sum = 0;
    checkLazy(s, t, m, p);
    if(l <= m)  sum = getSum(l, r, s, m, p << 1);
    if(m < r)   sum += getSum(l, r, m + 1, t, (p << 1) | 1);
    return sum;
}
void update(int l, int r, int v, int s, int t, int p) {
    if(l <= s && t <= r) {
        d[p] += (t - s + 1) * v;
        lazy[p] += v;
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
    int n, Q, l, r, v;
    char ch[2];
    cin >> n >> Q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, n, 1);
    while(Q--) {
        cin >> ch >> l >> r;
        if(ch[0] == 'Q')    cout << getSum(l, r, 1, n, 1) << endl;
        else {
            cin >> v;
            update(l, r, v, 1, n, 1);
        }
    }
    return 0;
}
