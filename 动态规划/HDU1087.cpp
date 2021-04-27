#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
int num[maxn], dp[maxn];
int main() {
    int n;
    while(cin >> n && n) {
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            cin >> num[i];
            dp[i] = num[i];
        }
        for(int i = 1; i <= n; i++) {
            int maxx = 0;
            for(int j = 1; j < i; j++) {
                if(num[i] > num[j]) maxx = max(maxx, dp[j] + num[i]);
            }
            dp[i] = max(dp[i], maxx);
            ans = max(ans, dp[i]);
        }
        cout << ans << endl;
    }
    
    return 0;
}
