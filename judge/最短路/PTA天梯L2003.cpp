#include<bits/stdc++.h>
using namespace std;
struct cmp {
    using pdd = pair<double, double>;
    bool operator() (pdd& lhs, pdd& rhs) {
        return lhs.first > rhs.first;
    }
};
int main() {
    int n, D;
    scanf("%d%d", &n, &D);
    using pdd = pair<double, double>;
    vector<pdd> q(n);
    for(int i = 0; i < n; i++) {
        scanf("%lf", &(q[i].second));
    }
    double s;
    for(int i = 0; i < n; i++) {
        scanf("%lf", &s);
        q[i].first = s / q[i].second;
    }
    sort(q.begin(), q.end(), cmp());
    double sum = 0;
    for(pdd& it: q) {
        if(it.second >= D) {
            sum += it.first * D;
            break;
        }else {
            sum += it.first * it.second;
            D -= it.second;
        }
    }
    printf("%.2f\n", sum);
    return 0;
}