#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
struct C {
    char ch;
    long long val;
}arr[maxn];
long long pn = 0, nn = 0, P = 0, N = 0;
map<double, double> m;
int main() {
    int n;
    double ans = 0, fpr;
    scanf("%d", &n);
    m[0] = 0;
    for(int i = 0; i < n; i++) {
        scanf(" %c", &arr[i].ch);
        scanf("%lld", &arr[i].val);
        if(arr[i].ch == '+') pn++;
        else nn++;
    }
    sort(arr, arr + n, [](const C& x, const C& y){
        return x.val < y.val;
    });
    for(int i = 0; i < n; i++) {
        if(i && arr[i].val == arr[i - 1].val) {
            if(arr[i].ch == '+') P++;
            else N++;
            continue;
        }
        fpr = double(nn - N) / nn;
        m[fpr] = max(m[fpr], double(pn - P) / pn);
        if(arr[i].ch == '+') P++;
        else N++;
    }
    auto r = ++m.begin();
    for(auto it = m.begin(); r != m.end(); it = r, r++) {
        ans += (r->first - it->first) * it->second;
    }
    printf("%.15lf\n", ans);
    return 0;
}
