#include <bits/stdc++.h>
using namespace std;
const int maxn = 50000 + 5;
int a[maxn];
class SegmentTree {
private:
    int* d;
public:
    SegmentTree(size_t n): d(new int[n << 2]()) {}
    ~SegmentTree() {
        delete[] d;
    }

    void build(int s, int t, int p) {
        if(s == t) {
            d[p] = a[s];
            return;
        } 
        int m = (s + t) >> 1;
        build(s, m, 2 * p);
        build(m + 1, t, 2 * p + 1);
        d[p] = d[2 * p] + d[2 * p + 1];
    }

    int getSum(int l, int r, int s, int t, int p) {
        if(l <= s && t <= r) {
            return d[p];
        }
        int m = (s + t) >> 1, sum = 0;
        if(l <= m)  sum += getSum(l, r, s, m, 2 * p);
        if(m < r)   sum += getSum(l, r, m + 1, t, 2 * p + 1);
        return sum;
    }
    
    void update(int l, int v, int s, int t, int p) {
        if(s == t) {
            d[p] += v;
            return;
        }
        int m = (s + t) >> 1;
        if(l <= m)  update(l, v, s, m, 2 * p);
        else   update(l, v, m + 1, t, 2 * p + 1);
        d[p] = d[2 * p] + d[2 * p + 1]; 
    }

    void clear(size_t n) {
        memset(d, 0, n << 2);
    }

};

int main() {
    int T, n = 0, cnt = 0, l, r;
    char choose[10];
    SegmentTree s(maxn);
    scanf("%d", &T);
    while(T--) {
        printf("Case %d:\n", ++cnt);
        s.clear(n);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }
        s.build(1, n, 1);
        char ch;
        while(scanf("%s", choose) != EOF && (ch = choose[0]) != 'E') {
            scanf("%d%d", &l, &r);
            if(ch == 'Q') {
                printf("%d\n", s.getSum(l, r, 1, n, 1));
            }else if(ch == 'A'){
                s.update(l, r, 1, n, 1);
            }else {
                s.update(l, -r, 1, n, 1);
            }
        }
    }
    return 0;
}
