#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
int a[maxn];
int main() {
    ios::sync_with_stdio(false);
    int t, n;
    cin >> t;
    while(t--) {
        int minp, maxp, minn = maxn, maxx = 0;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(a[i] > maxx) {
                maxp = i;
                maxx = a[i];
            }
            if(a[i] < minn) {
                minp = i;
                minn = a[i];
            }
        }
        int case1 = min(max(maxp, minp) + 1, n - min(maxp, minp));
        cout << min(case1, min(maxp, minp) + 1 + n - max(maxp, minp)) << endl;
    }
    return 0;
}
