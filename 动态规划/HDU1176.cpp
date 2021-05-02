#include<bits/stdc++.h>
using namespace std;
const int mr = 10 + 5;
const int maxt = 100000 + 5;
int dp[maxt][mr];
int pro[maxt][mr];
int main() {
    ios::sync_with_stdio(false);
    int t, time, place, n, maxtime, ans = 0;
    while(cin >> t && t) {
        maxtime = 0;
        ans = 0;
        memset(dp, 0, sizeof dp);
        memset(pro, 0, sizeof pro);
        for(int i = 0; i < t; i++) {
            cin >> place >> time;
            pro[time][place]++;
            maxtime = max(maxtime, time);
        }
        for(int i = 0; i <= 10; i++) {
            dp[maxtime][i] = pro[maxtime][i];
        }
        for(int i = maxtime - 1; i >= 0; i--) {
            for(int j = 0; j <= 10; j++) {
                for(int k = max(0, j - 1); k <= min(10, j + 1); k++) {
                    dp[i][j] = max(dp[i][j], dp[i + 1][k] + pro[i][j]);
                }
            }
        }
        cout << dp[0][5] << endl;
    }
    return 0;
}