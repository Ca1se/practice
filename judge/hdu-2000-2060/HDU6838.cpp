#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const ll MOD = 998244353;
ll m, p, q;
ll fast_mod(ll a,ll b) {
	ll ans = 1;
    while(b){
        if(b & 1)   ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
ll solve() {
    ll a = 100 * m * (p - q) + q * p, b = 100 * p, ans;
    ans = ((a % MOD) * fast_mod(b, MOD - 2)) % MOD;
    if(ans < 0){
        ans = MOD - abs(ans);
    }
    return ans;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> m >> p >> q;
        cout << solve() << endl;
    }
    return 0;
}