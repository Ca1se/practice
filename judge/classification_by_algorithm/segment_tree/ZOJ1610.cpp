#include <bits/stdc++.h>
using namespace std;
const int maxn = 8000 + 5;
struct interval {
    int f, t, v;
}seq[maxn];
map<int, int> mp;
int maxx = 0, minn = 0;
int d[maxn << 2] = {0}, lazy[maxn << 2] = {0}, line[maxn];
void checkLazy(int s, int t, int p) {
    if(lazy[p] && s != t) {
        d[p << 1] = d[(p << 1) | 1] = lazy[p << 1] = lazy[(p << 1) | 1] = lazy[p];
        lazy[p] = 0;
    }
}
void update(int l, int r, int v, int s, int t, int p) {
    if(l <= s && t <= r) {
        d[p] = v;
        lazy[p] = v;
        return;
    }
    int m = (s + t) >> 1;
    checkLazy(s, t, p);
    if(l <= m)  update(l, r, v, s, m, p << 1);
    if(m < r)   update(l, r, v, m + 1, t, (p << 1) | 1);
    if(d[p << 1] == d[(p << 1) | 1]) {
        d[p] = d[p << 1];
    }else {
        d[p] = 0;
    }
}
void get(int s, int t, int p) {
    if(d[p]) {
        if((s == minn || line[s - 1] != d[p]) && (t == maxx || line[t + 1] != d[p])) {
            mp[d[p]]++;
        }else if(s != minn && t != maxx && line[s - 1] == d[p] && line[t + 1] == d[p]) {
            mp[d[p]]--;
        }
        line[s] = line[t] = d[p];
        return;
    }
    if(s != t) {
        int m = (s + t) >> 1;
        checkLazy(s, t, p);
        get(s, m, p << 1);
        get(m + 1, t, (p << 1) | 1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    int n;
    while(cin >> n) {
        memset(d + minn, 0, sizeof(int) * ((maxx - minn) << 2));
        memset(lazy + minn, 0, sizeof(int) * ((maxx - minn) << 2));
        memset(line, 0, sizeof line);
        mp.clear();
        maxx = 0, minn = 0x3f3f3f3f;
        for(int i = 0; i < n; i++) {
            auto& it = seq[i];
            cin >> it.f >> it.t >> it.v;
            it.v++, it.t--;
            maxx = max(maxx, it.t);
            minn = min(minn, it.f);
        }
        for(int i = 0; i < n; i++) {
            update(seq[i].f, seq[i].t, seq[i].v, minn, maxx, 1);
        }
        get(minn, maxx, 1);
        for(const auto& it: mp) {
            cout << it.first - 1 << " " << it.second << endl;
        }
        cout << endl;
    }
    return 0;
}
