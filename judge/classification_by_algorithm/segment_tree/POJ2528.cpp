//离散化使用左闭右开区间
#include <cstdio>
#include <set>
#include <cstring>
#define pii pair<int, int>
using namespace std;
const int maxn = 1e5 + 5;
struct interval {
    int l, r, v;
    interval() {}
}is[maxn];
pii seq[maxn];
set<int> rs;
set<int> ns;
int d[maxn << 2] = {0};
int lazy[maxn << 2] = {0};
void build(int l, int r, int v, int s, int t, int p) {
    if(l <= is[s].l && is[t].r - 1 <= r) {
        d[p] = v;
        lazy[p] = v;
        return ;
    }
    int m = (s + t) >> 1;
    if(lazy[p]) {
        d[p << 1] = d[(p << 1) | 1] = lazy[p << 1] = lazy[(p << 1) | 1] = lazy[p];
        lazy[p] = 0;
    }
    if(l <= is[m].l)    build(l, r, v, s, m, p << 1);
    if(is[m].r <= r)    build(l, r, v, m + 1, t, (p << 1) | 1);
    if(d[p << 1] == d[(p << 1) | 1]) {
        d[p] = d[p << 1];
    }else {
        d[p] = 0;
    }
}
void get(int s, int t, int p) {
    if(d[p]) {
        ns.insert(d[p]);
        return;
    }
    if(s != t) {
        int m = (s + t) >> 1;
        if(lazy[p]) {
            d[p << 1] = d[(p << 1) | 1] = lazy[p << 1] = lazy[(p << 1) | 1] = lazy[p];
            lazy[p] = 0;
        }
        get(s, m, p << 1);
        get(m + 1, t, (p << 1) | 1);
    }
}
int main() {
    int c, n = 0, r;
    scanf("%d", &c);
    while(c--) {
        rs.clear();
        ns.clear();
        memset(d, 0, sizeof(int) * (n << 2));
        memset(lazy, 0, sizeof(int) * (n << 2));
        r = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            pii& t = seq[i];
            scanf("%d%d", &t.first, &t.second);
            rs.insert(t.first);
            rs.insert(t.second + 1);
        }
        for(set<int>::iterator i = rs.begin(); i != (--rs.end());) {
            is[r].l = *i;
            is[r++].r = *(++i);
        }
        for(int i = 0; i < n; i++) {
            build(seq[i].first, seq[i].second, i + 1, 0, r - 1, 1);
        }
        get(0, r - 1, 1);
        printf("%d\n", (int) ns.size());
    }
    return 0;
}
