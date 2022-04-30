#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
struct Point {
    Point(int t, int x, int y): t(t), x(x), y(y) {}
    Point() = default;
    int x, y, t;
};
int dp[maxn];
int main() {
    int n, m, x, y, t;
    Point arr[maxn];
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> t >> x >> y;
        arr[i] = Point(t, x, y);
    }
    arr[0].x = arr[0].y = 1; arr[0].t = 0; dp[0] = 0;
    for(int i = 1; i <= m; i++){
        for(int j = max(0, i - 1 - 4 * n); j < i; j++){
            if(dp[j] != -1 && (abs(arr[i].x - arr[j].x) + abs(arr[i].y - arr[j].y)) <= (arr[i].t - arr[j].t)){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int ans = 0;
    cout << *max_element(dp, dp + m + 1) << endl;
}