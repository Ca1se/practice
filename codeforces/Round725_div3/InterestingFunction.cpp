#include <bits/stdc++.h>
using namespace std;
using ll = long long;
map<int, ll> mp = {{1, 1}, {10, 11}};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t, l, r;

    for(int i = 100; i <= int(1e9); i *= 10) {
        mp[i] = 10 * mp[i / 10] + 1;
    } 

    cin >> t;
    while(t--) {
        cin >> l >> r;
        int ans = r - l;
        int tmp = 10;
        while(tmp <= r) {
            l = l / tmp * tmp;
            ans += (r - l) / tmp;
            tmp *= 10;
        }
        cout << ans << endl;
    }
    return 0;
}
