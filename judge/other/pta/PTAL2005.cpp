#include<bits/stdc++.h>
using namespace std;
const int maxnum = 1e9 + 5;
const int maxn = 50 + 5;
const int maxm = 1e4 + 5;
const int maxk = 2000 + 5;
map<int, int> ms[maxn];
int main() {
    int n, m, t, k, c1, c2;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &m);
        for(int j = 0; j < m; j++) {
            scanf("%d", &t);
            ms[i][t]++;
        }
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        scanf("%d%d", &c1, &c2);
        int len1 = ms[c1 - 1].size(), len2 = ms[c2 - 1].size(), same = 0;
        const auto& itmax = len1 >= len2 ? ms[c1 - 1] : ms[c2 - 1];
        const auto& itmin = len1 >= len2 ? ms[c2 - 1] : ms[c1 - 1];
        for(auto it = itmin.begin(); it != itmin.end(); it++) {
            if(itmax.find(it->first)->second != 0)   same++;
        }
        printf("%.2f%\n", (float) same / (len1 + len2 - same) * 100);
    }
    return 0;
}
