#include <bits/stdc++.h>
using namespace std;
const int maxn = 2 * 1e5 + 5;
int a[maxn];
int appear[(int) 1e4 + 5];
int main() {
    ios::sync_with_stdio(false);
    int t, n;
    cin >> t;
    while(t--) {
        memset(appear, 0, sizeof appear);
        int sum = 0, maxx = 0;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            sum += a[i];
            maxx = max(a[i], maxx);
            appear[a[i]]++;
        }
        if(sum % n) {
            cout << -1 << endl;
            continue;
        }
        int avg = sum / n, ans = 0;
        for(int i = avg + 1; i <= maxx; i++) {
            ans += appear[i];
        } 
        cout << ans << endl;
    }
    return 0;
}
