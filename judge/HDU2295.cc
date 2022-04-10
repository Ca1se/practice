#include <bits/stdc++.h>
using namespace std;
const int maxc = 50 + 5;
const int maxr = 50 + 5;
const int maxl = maxc * maxr;
const double eps = 1e-8;

struct Point {
        int x, y;
} city[maxc], radar[maxc];

int n, m, k, idx;
int siz[maxl], col[maxl], row[maxl];
int L[maxl], R[maxl], U[maxl], D[maxl];
int first[maxl];
bool vis[maxl];


void build(int r, int c) {
        for(int i = 0; i <= c; i++) {
                L[i] = i - 1, R[i] = i + 1;
                U[i] = D[i] = i;
        siz[i] = 0;
        }
        L[0] = c, R[c] = 0, idx = c;
    for(int i = 0; i <= r; i++) first[i] = 0;
}

inline void remove(int c) {
    for(int i = D[c]; i != c; i = D[i]) {
        R[L[i]] = R[i], L[R[i]] = L[i];
    }
}

inline void recover(int c) {
    for(int i = U[c]; i != c; i = U[i]) {
        R[L[i]] = L[R[i]] = i;
    }
}

inline void insert(int r, int c) {
        col[++idx] = c, row[idx] = r, siz[idx]++;
        U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
        if(!first[r]) first[r] = L[idx] = R[idx] = idx;
        else {
                L[idx] = first[r], R[idx] = R[first[r]];
                L[R[first[r]]] = idx, R[first[r]] = idx;
        }
}

int predict() {
    int ret = 0;
    for(int i = R[0]; i != 0; i = R[i]) vis[i] = true;
    for(int i = R[0]; i != 0; i = R[i]) {
        if(vis[i]) {
            ret++;
            vis[i] = false;
            for(int j = D[i]; j != i; j = D[j]) {
                for(int k = R[j]; k != j; k = R[k]) {
                    vis[col[k]] = false;
                }
            }
        }
    }
    return ret;
}

bool dance(int cnt) {
    if(cnt + predict() > k) return false;
    if(cnt > k) return false;
        if(!R[0]) return true;
        int c = R[0];
        for(int i = R[c]; i != 0; i = R[i]) if(siz[c] > siz[i]) c = i;
        for(int i = D[c]; i != c; i = D[i]) {
        remove(i);
                for(int j = R[i]; j != i; j = R[j]) remove(j);
                if(dance(cnt + 1)) return true;
                for(int j = L[i]; j != i; j = L[j]) recover(j);
        recover(i);
        }
        return false;
}

inline double cdist(const Point& x, const Point& y) {
        return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}

int main() {
        int t;
        scanf("%d", &t);
        while(t--) {
                scanf("%d%d%d", &n, &m, &k);
                for(int i = 0; i < n; i++) {
                        scanf("%d%d", &city[i].x, &city[i].y);
                }
                for(int i = 0; i < m; i++) {
                        scanf("%d%d", &radar[i].x, &radar[i].y);
                }
        double l = 0, r = 1e5;
        while(r - l >= eps) {
            double mid = (l + r) / 2;
            build(m, n);
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(cdist(radar[i], city[j]) < mid - eps) insert(i + 1, j + 1);
                }
            }
            if(dance(0)) r = mid - eps;
            else l = mid + eps;
        }
        printf("%.6lf\n", l);
        }
        return 0;
}
