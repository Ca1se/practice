#include <bits/stdc++.h>
using namespace std;
const int maxr = 5280;
const int maxc = 67;
const int maxl = maxr * maxc;

int col[maxl], row[maxl], front[maxr], siz[maxc + 5];
int L[maxl], R[maxl], U[maxl], D[maxl];
char ans[11][11], mp[11][11];
int idx;

struct Point {
    Point(int x, int y): x(x), y(y) {}
    int x, y;
};

vector<Point> part[12] = {
    {{1, 0}, {0, 1}},
    {{1, 0}, {2, 0}, {3, 0}},
    {{0, 1}, {1, 0}, {2, 0}},
    {{1, 0}, {0, 1}, {1, 1}},
    {{0, 1}, {0, 2}, {1, 2}, {2, 2}},
    {{1, 0}, {1, 1}, {2, 0}, {3, 0}},
    {{0, 1}, {1, 0}, {2, 0}, {2, 1}},
    {{1, 0}, {0, 1}, {1, 1}, {2, 0}},
    {{1, 0}, {2, 0}, {2, 1}, {3, 1}},
    {{1, 0}, {1, -1}, {1, 1}, {2, 0}},
    {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
    {{0, 1}, {1, 0}, {2, 0}, {3, 0}}
};

int qp[10] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
int angle[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool g[12] = {};
bool g1[12] = {};

bool ok(int x, int y) {
    if(x < 1 || y < 1 || y < x || x > 10 || y > 10) return false;
    return true;
}

void build(int r, int c) {
    for(int i = 0; i <= c; i++) {
        L[i] = i - 1, R[i] = i + 1;
        U[i] = D[i] = i;
    }
    L[0] = c, R[c] = 0, idx = c;
    memset(front, 0, sizeof front);
    memset(siz, 0, sizeof siz);
}

void remove(int c) {
    R[L[c]] = R[c], L[R[c]] = L[c];
    for(int i = D[c]; i != c; i = D[i]) {
        for(int j = R[i]; j != i; j = R[j]) {
            U[D[j]] = U[j], D[U[j]] = D[j], siz[col[j]]--;
        }
    }
}

void recover(int c) {
    for(int i = U[c]; i != c; i = U[i]) {
        for(int j = L[i]; j != i; j = L[j]) {
            U[j] = D[j] = j, siz[col[j]]++;
        }
    }
    R[c] = L[c] = c;
}

void insert(int r, int c) {
    col[++idx] = c, row[idx] = r, siz[c]++;
    U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
    if(front[r] == 0) front[r] = R[idx] = L[idx] = idx;
    else  {
        L[idx] = front[r], R[idx] = R[front[r]];
        L[R[front[r]]] = idx, R[front[r]] = idx;
    }
}

bool dance() {
    if(R[0] == 0) return true;
    int c = R[0];
    for(int i = R[0]; i != 0; i = R[i]) if(siz[c] > siz[i]) c = i;
    remove(c);
    for(int i = D[c]; i != c; i = D[i]) {
        int pos = (row[i] - 1) / 96;
        int wh = (row[i] - pos * 96 - 1) / 8;
        int an = (row[i] - pos * 96 - wh * 8 - 1) / 2;
        int re = row[i] - pos * 96 - wh * 8 - an * 2 - 1;
        int y;
        for(y = 0; y < 10; y++) if(qp[y] >= (pos + 1)) break;
        int x = pos - (1 + y) * y / 2;
        ans[y][x] = 'A' + wh;
        for(const auto& it: part[wh]) {
            int xx = x + (it.x * angle[an][1] - it.y * angle[an][0]) * (re ? -1 : 1);
            int yy = y + it.y * angle[an][1] + it.x * angle[an][0];
            ans[yy][xx] = 'A' + wh;
        }
        for(int j = R[i]; j != i; j = R[j]) remove(col[j]);
        if(dance()) return true;
        for(int j = L[i]; j != i; j = L[j]) recover(col[j]);
    }
    recover(c);
    return false;
}

inline void insert(int pos, int wh, int an, int re, const vector<Point>& vec) {
    int r = (pos - 1) * 96 + wh * 8 + an * 2 + re + 1;
    insert(r, pos);
    for(const auto& it: vec) {
        insert(r, it.y * (it.y - 1) / 2 + it.x);
    }
    insert(r, 56 + wh);
}

int main() {
    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= i; j++) {
            scanf(" %c", &mp[i][j]);
            if(mp[i][j] != '.') g[mp[i][j] - 'A'] = true;
        }
    }    
    build(5280, 67);
    vector<Point> vec;
    int cnt = 0;
    for(int y = 1; y <= 10; y++) {
        for(int x = 1; x <= y; x++) {
            if(mp[y][x] == '.') {
                for(int i = 0; i < 12; i++) {
                    if(g[i]) continue;
                    for(int j = 0; j < 4; j++) {
                        for(int k = 0; k < 2; k++) {
                            bool jug = true;
                            for(const auto& it: part[i]) {
                                int xx = x + (it.x * angle[j][1] - it.y * angle[j][0]) * (k ? -1 : 1);
                                int yy = y + it.y * angle[j][1] + it.x * angle[j][0];
                                if(!ok(xx, yy) || mp[yy][xx] != '.') {
                                    jug = false;
                                    break;
                                }
                                vec.emplace_back(xx, yy);
                            }
                            if(jug) {
                                insert(y * (y - 1) / 2 + x, i, j, k, vec);
                                cnt++;
                            }
                            vec.clear();
                        }
                    }
                }
            }else {
                if(g1[mp[y][x] - 'A']) continue;
                bool ju = true;
                for(int j = 0; ju && j < 4; j++) {
                    for(int k = 0; ju && k < 2; k++) {
                        bool jug = true;
                        for(const auto& it: part[mp[y][x] - 'A']) {
                            int xx = x + (it.x * angle[j][1] - it.y * angle[j][0]) * (k ? -1 : 1);
                            int yy = y + it.y * angle[j][1] + it.x * angle[j][0];
                            if(!ok(xx, yy) || mp[yy][xx] != mp[y][x]) {
                                jug = false;
                                break;
                            }
                            vec.emplace_back(xx, yy);
                        }
                        if(jug) {
                            insert(y * (y - 1) / 2 + x, mp[y][x] - 'A', j, k, vec);
                            g1[mp[y][x] - 'A'] = true;
                            ju = false;
                            cnt++;
                        }
                        vec.clear();
                    }
                }
            }
        }
    }
    cout << cnt << endl;
    if(dance()) {
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j <= i; j++) {
                printf("%c", ans[i][j]);
            }
            printf("\n");
        }
    }else {
        printf("No solution\n");
    }
    return 0;
}
