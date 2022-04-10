#include <bits/stdc++.h>
using namespace std;
const int maxn = 3 * 1e5 + 5;
int arr[maxn];
bool tree[maxn << 2];

void init(int l, int r, int p) {
    if(l == r) {
        tree[p] = true;
        return;
    }
    int m = (l + r) >> 1;
    init(l, m, p << 1);
    init(m + 1, r, (p << 1) | 1);
    tree[p] = tree[p << 1] && tree[(p << 1) | 1] && arr[m] <= arr[m + 1];
}
int m;
void modify(int l, int r, int ql, int p) {
    if(l == r && ql == l) {
        arr[ql] = m;
        return;
    }
    int m = (l + r) >> 1;
    if(m >= ql) modify(l, m, ql, p << 1);
    else modify(m + 1, r, ql, (p << 1) | 1);
    tree[p] = tree[p << 1] && tree[(p << 1) | 1] && arr[m] <= arr[m + 1];
}

bool quest(int l, int r, int ql, int qr, int p) {
    if(ql <= l && r <= qr) return tree[p];
    int m = (l + r) >> 1;
    bool res = true;
    int cnt = 0;
    if(m >= ql) {
        res = quest(l, m, ql, qr, p << 1);
        cnt++;
    }
    if(res && m < qr) {
        res = quest(m + 1, r, ql, qr, (p << 1) | 1);
        cnt++;
    }
    if(cnt == 2) res = res && arr[m] <= arr[m + 1];
    return res;
}

int main() {
    int n, qn, opt, l, r;
    scanf("%d%d", &n, &qn);
    for(int i = 1; i <= n; i++) {
        scanf("%d", arr + i);
    }
    init(1, n, 1);
    while(qn--) {
        scanf("%d%d%d", &opt, &l, &r);
        if(opt == 1) {
            m = r;
            modify(1, n, l, 1);
        }else {
            if(quest(1, n, l, r, 1)) {
                printf("Yes\n");
            }else {
                printf("No\n");
            }
        }
    }
    return 0;
}
