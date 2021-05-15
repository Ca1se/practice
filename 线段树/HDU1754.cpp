#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 5;
int score[maxn];
int d[maxn << 2] = {0};

void build(int s, int t, int p) {
    if(s == t) {
        d[p] = score[s];
        return ;
    }
    int m = (s + t) >> 1;
    if(s <= m)  build(s, m, p << 1);
    if(m < t)   build(m + 1, t, (p << 1) | 1);
    d[p] = max(d[p << 1], d[(p << 1) | 1]);
}

int getMax(int l, int r, int s, int t, int p) {
    if(l <= s && t <= r) {
        return d[p];
    }
    int m = (s + t) >> 1, maxx = 0;
    if(l <= m)  maxx = getMax(l, r, s, m, p << 1);
    if(m < r)   maxx = max(maxx, getMax(l, r, m + 1, t, (p << 1) | 1));
    return maxx;
}

void update(int f, int v, int s, int t, int p) {
    if(s == t) {
        d[p] = v;
        return;
    }
    int m = (s + t) >> 1;
    if(f <= m)  update(f, v, s, m, p << 1);
    else if(m < f)  update(f, v, m + 1, t, (p << 1) | 1);
    d[p] = max(d[p << 1], d[(p << 1) | 1]);
}

int main() {
    int n, m, l, r;
    char ch[2];
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", score + i);
        }
        build(1, n, 1);
        while(m--) {
            scanf("%s%d%d", ch, &l, &r);
            if(ch[0] == 'Q')   printf("%d\n", getMax(l, r, 1, n, 1));
            else update(l, r, 1, n, 1);
        }
        memset(d, 0, n << 2);
    }
    return 0;
}
