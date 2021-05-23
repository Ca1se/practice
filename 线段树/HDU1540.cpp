#include <bits/stdc++.h>
using namespace std;
const int maxn = 50000 + 5;
int lmax[maxn << 2];
int rmax[maxn << 2];
void build(int s, int t, int p) {
    if(s == t) {
        lmax[p] = rmax[p] = 1;
        return;
    }
    int m = (s + t) >> 1;
    build(s, m, p << 1);
    build(m + 1, t, (p << 1) | 1);
    lmax[p] = lmax[p << 1] + (lmax[p << 1] == (m - s + 1) ? lmax[(p << 1) | 1] : 0);
    rmax[p] = rmax[(p << 1) | 1] + (rmax[(p << 1) | 1] == (t - m) ? rmax[p << 1] : 0);
}
void update(int c, int v, int s, int t, int p) {
    if(s == t) {
        lmax[p] = rmax[p] = v;
        return;
    }
    int m = (s + t) >> 1;
    if(c <= m)  update(c, v, s, m, p << 1);
    else        update(c, v, m + 1, t, (p << 1) | 1);
    lmax[p] = lmax[p << 1] + (lmax[p << 1] == (m - s + 1) ? lmax[(p << 1) | 1] : 0);
    rmax[p] = rmax[(p << 1) | 1] + (rmax[(p << 1) | 1] == (t - m) ? rmax[p << 1] : 0);
}
int get(int c, int s, int t, int p) {
    if(s == t) {
        return lmax[p];
    }
    int m = (s + t) >> 1;
    if(c <= m) {
        if((m - c + 1) <= rmax[p << 1]) {
            return rmax[p << 1] + lmax[(p << 1) | 1];
        }else {
            return get(c, s, m, p << 1);
        }
    }else {
        if((c - m) <= lmax[(p << 1) | 1]) {
            return lmax[(p << 1) | 1] + rmax[p << 1];
        }else {
            return get(c, m + 1, t, (p << 1) | 1);
        }
    }
}
int main() {
    int n, m, c;
    char ch[2];
    while(scanf("%d%d", &n, &m) != EOF) {
        stack<int> s;
        build(1, n, 1);
        while(m--) {
            scanf("%s", ch);
            if(ch[0] == 'R') {
                update(s.top(), 1, 1, n, 1);
                s.pop();
            }else {
                scanf("%d", &c);
                if(ch[0] == 'D') {
                    s.push(c);
                    update(c, 0, 1, n, 1);
                }else {
                    printf("%d\n", get(c, 1, n, 1));
                }
            }
        }
    }
    return 0;
}
