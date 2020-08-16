/**
 *  给定两个数列,输出两者公共最大长度
 *   如: 1523645, 52152348 -> 5(15234)
 * 
 */
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
int n, m, p[maxn][maxn];
char s1[maxn], s2[maxn];
int dp(int n, int m) {
    if(p[n][m]) return p[n][m];
    if(n == 0 || m == 0)    return 0;
    if(s1[n] == s2[m])  p[n][m] = dp(n - 1, m - 1) + 1;
    else    p[n][m] = max(dp(n - 1, m), dp(n, m - 1));
    return p[n][m];
}
int main() {
    memset(p, 0, sizeof(p));
    cin >> n >> m;
    cin >> s1 + 1 >> s2 + 1;
    cout << dp(n, m) << endl;
    return 0;
}