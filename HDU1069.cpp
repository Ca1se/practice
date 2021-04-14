#include<bits/stdc++.h>
using namespace std;
const int maxn = 30 + 5;
struct block {
    block(int x, int y, int z): x(x), y(y), z(z) {}
    int x, y, z;
};
vector<block> q;
int ans = 0, dp[maxn * 3], vis[maxn * 3];
int n, cnt = 1, x, y, z;
int dfs(int pos) {
    if(vis[pos])    return dp[pos];
    vis[pos] = true;
    block& b = q[pos];
    for(int i = 0; i < n * 3; i++) {
        block& t = q[i];
        if((b.x > t.x && b.y > t.y) || (b.x > t.y && b.y > t.x))
            dp[pos] = max(dp[pos], dfs(i) + b.z);
    }     
    ans = max(ans, dp[pos]);
    return dp[pos];
}
int main() {
    ios::sync_with_stdio(false);
    while(cin >> n && n) {
        q.clear();
        ans = 0;
        memset(vis, 0, sizeof vis);
        for(int i = 0; i < n; i++) {
            cin >> x >> y >> z;
            q.emplace_back(x, y, z);
            q.emplace_back(y, z, x);
            q.emplace_back(z, x, y);
            dp[i * 3] = z;
            dp[i * 3 + 1] = x;
            dp[i * 3 + 2] = y;
        }
        for(int i = 0; i < n * 3; i++)
            dfs(i);
        cout << "Case " << cnt++ << ": maximum height = " << ans << endl;
    } 
    return 0;
}