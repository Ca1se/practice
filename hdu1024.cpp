#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
const int maxn = 1e6 + 5;
int num[maxn], dp[maxn], maxx[maxn];
int main() {
    int m, n, temp;
    while(cin >> m >> n){
        memset(dp, 0, sizeof(dp));
        memset(maxx, 0, sizeof(maxx));
        for(int i = 1; i <= n; i++){
            cin >> num[i];
        }
        for(int i = 1; i <= m; i++){
            temp = -0x3f3f3f3f;
            for(int j = i; j <= n; j++){
                dp[j] = max(dp[j - 1], maxx[j - 1]) + num[j];
                maxx[j - 1] = temp;
                temp = max(temp, dp[j]);
            }
        }
        cout << temp << endl;
    }
    return 0;
}