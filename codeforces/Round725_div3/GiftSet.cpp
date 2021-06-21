#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t, x, y, a, b;
    cin >> t;
    while(t--) {
        int ans = 0;
        cin >> x >> y >> a >> b;
        if(a == b) {
            cout << min(x, y) / a << endl;
            continue;
        }
        if(a < b) swap(a, b);
        int l = 0, r = max(x, y) / min(a, b);
        while(l <= r) {
            int mid = (l + r) >> 1;
            double l1 = (x -  double(b) * mid) / (a - b), l2 = double(y - double(a) * mid) / (b - a);
            l2 = max(l2, 0.0);
            l1 = min(l1, double(mid));
            if(int(l2) != l2) l2 = int(l2) + 1;
            if(l2 <= l1) {
                ans = max(ans, mid);
                l = mid + 1;
            }else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
