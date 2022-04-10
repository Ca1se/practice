#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 4 * 1e5 + 5;
int arr[2][maxn], vis[maxn], mp[maxn];
void solve(int p) {
    if(!vis[p]) {
        vis[p]++;
        solve(mp[p]);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t, n;
    cin >> t;
    while(t--) {
        memset(vis, 0, sizeof vis);
        memset(mp, 0, sizeof mp);
        cin >> n;
        int have = 0;
        long long ans = 1;
        for(int i = 0; i < n; i++) {
            cin >> arr[0][i];
        }
        for(int i = 0; i < n; i++) {
            cin >> arr[1][i];
        }
        for(int i = 0; i < n; i++) {
            mp[arr[1][i]] = arr[0][i];
        } 
        for(int i = 0; i < n; i++) {
            if(!vis[arr[1][i]]) {
                have++;
                solve(arr[1][i]);
            }
        }
        for(int i = 0; i < have; i++) {
            ans = (ans * 2) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}

