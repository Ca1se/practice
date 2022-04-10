#include <bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5;
const int maxm = 1e5 + 5;
const int msumq = 300000 + 5;
 
struct Card {
    int d, k, c;
}cards[maxn];
pair<int, int> dqs[maxm];
pair<int, int> fp[maxm];
long long dp[msumq];
 
int get_date_index(int l, int r, int p) {
    if(l == r) {
        return fp[l].second;
    }else {
        int mid = (l + r) >> 1;
        if(fp[mid].first == p) {
            return fp[mid].second;
        }else if(fp[mid].first < p) {
            return get_date_index(mid + 1, r, p);
        }else {
            return get_date_index(l, mid, p);
        }
    }
}
 
int main() {
    int n, m, rm = 0, r, sumq = 0, dq, kq, qsum = 0;
    scanf("%d%d%d", &n, &m, &r);
    for(int i = 0; i < n; i++) {
        scanf("%d%d%d", &cards[i].d, &cards[i].k, &cards[i].c);
    }
    cards[n].d = 1, cards[n].k = 1, cards[n].c = r;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &dqs[rm].first, &dqs[rm].second);
        if(dqs[rm].second) rm++;
    }
    sort(dqs, dqs + rm, [](const pair<int, int>& x, const pair<int, int>& y) {
        return x.first < y.first;
    });
    for(int i = 0; i < rm; i++) {
        fp[i].first = dqs[i].first;
        fp[i].second = sumq + 1;
        sumq += dqs[i].second;
    }
    auto it = dqs;
    dp[0] = 0;
    for(int i = 1; i <= sumq; i++) {
        dq = get_date_index(0, rm - 1, max(0, it->first - cards[0].d + 1)) - 1, kq = i - cards[0].k;
        dp[i] = dp[max(dq, kq)] + cards[0].c;
        for(int k = 1; k < n + 1; k++) {
            dq = get_date_index(0, rm - 1, max(0, it->first - cards[k].d + 1)) - 1, kq = i - cards[k].k;
            dp[i] = min(dp[i], dp[max(dq, kq)] + cards[k].c);
        }
        if(++qsum == it->second) {
            qsum = 0;
            it++;
        }
    }
    printf("%lld\n", dp[sumq]);
    return 0;
}
