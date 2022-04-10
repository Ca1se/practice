#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
const int maxm = 1e2 + 5;
int money[maxn];
int n, m;
vector<int> ans;
int dp[maxm] = {0};
int remain[maxn];
bool ok = false;
int solve(int need, int pos) {
    if(dp[need] > 0)    return dp[need];
    if(pos != -1 && remain[pos] < need) return 0;
    if(need == 0) {
        ok = true;
        return 0;
    }
    int maxx = 0;
    for(int i = pos + 1; i < n; i++) {
        if(need - money[i] >= 0) {
            ans.push_back(money[i]);
            maxx = max(maxx, solve(need - money[i], i));
            if(ok)  return 0;
            ans.pop_back();
        }
    }
    return dp[need] = maxx;
}
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> money[i];
    }
    sort(money, money + n);
    remain[n - 1] = 0;
    for(int i = n - 2; i >= 0; i--) {
        remain[i] = remain[i + 1] + money[i + 1];
    }
    solve(m, -1);
    if(ok) {
        for(int i = 0; i < (int) ans.size(); i++) {
            cout << ans[i];
            if(i != (int) ans.size() - 1) cout << " ";
        }
        cout << "\n";
    }else {
        cout << "No Solution\n";        
    }
    return 0;
}
