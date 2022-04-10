#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 500 + 5;
const int maxw = 10000 + 5;
struct Coin {
    int p, w;
    bool operator< (const Coin& rhs) const {
        return w < rhs.w;
    }
}coins[maxn];
ll dp[maxw];
int main() {
    int t, E, F, n;
    cin >> t;
    while(t--) {
        memset(dp, -1, sizeof dp);
        cin >> E >> F;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> coins[i].p >> coins[i].w; 
            dp[coins[i].w] = coins[i].p; 
        }
        sort(coins, coins + n);
        dp[0] = 0;
        for(int i = 1; i <= F - E; i++) {
            for(int j = 0; j < n; j++) {
                if(coins[j].w > i) break;
                else if(dp[i - coins[j].w] < 0) continue;
                else {
                    if(dp[i] == -1) dp[i] = dp[i - coins[j].w] + coins[j].p;
                    else dp[i] = min(dp[i], dp[i - coins[j].w] + coins[j].p);
                }
            }
        }
        if(dp[F - E] != -1) {
            cout << "The minimum amount of money in the piggy-bank is " << dp[F - E] << ".\n";
        }else {
            cout << "This is impossible.\n";
        }
    }
    return 0;
}