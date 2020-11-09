#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll dp[55][3] = {0};
const int mod = 1e9 + 7;
int main() {
    char nums[50 + 5];
    cin >> nums;
    dp[0][(nums[0] - '0') % 3] = 1;
    for(int i = 1; i < strlen(nums); i++){
        int t = (nums[i] - '0') % 3;
        dp[i][t] = 1;
        for(int j = 0; j < 3; j++){
            dp[i][j] += (dp[i - 1][j] + dp[i - 1][(j + (3 - t)) % 3]) % mod;
        }
    }
    cout << dp[strlen(nums) - 1][0] % mod << endl;
    return 0;
}