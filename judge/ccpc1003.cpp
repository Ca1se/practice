#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, k;
int main() {
    ios::sync_with_stdio(false);
    ll t, minn, ans;
    cin >> t;
    while(t--){
        ans = 0, minn = LONG_LONG_MAX;
        ll tmp;
        cin >> n >> m >> k;
        for(int i = 0; i < m; i++){
            cin >> tmp;
            ans += abs(tmp - k) * 2;
            minn = min(tmp, minn);
        }
        if(minn < k){
            ans -= abs(minn - k) * 2;
        }
        cout << ans + 2 * (k - 1) << endl;
    }
    return 0;
}