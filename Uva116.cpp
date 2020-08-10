#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn = 10 + 5, maxm = 100 + 5;
int n, m, b[maxn][maxm], mark[maxn][maxm];
ll p[maxn][maxm];
void solve() {
    ll f = 0, ans = __LONG_LONG_MAX__;
    for(int i = m; i > 0; i--){
        for(int j = 1; j <= n; j++){
            if(i == m)  p[j][i] = b[j][i];
            else{
                int rows[3] = {j - 1, j, j + 1};
                if(j == 1)  rows[0] = n;
                if(j == n) rows[2] = 1;
                sort(rows, rows + 3);
                p[j][i] = __LONG_LONG_MAX__;
                for(int k = 0; k < 3; k++){
                    ll t = b[j][i] + p[rows[k]][i + 1];
                    if(p[j][i] > t){
                        p[j][i] = t;
                        mark[j][i] = rows[k];
                    }
                }
            }
            if(i == 1 && p[j][i] < ans){
                ans = p[j][i];
                f = j;
            }
        }
    }
    cout << f;
    for(int i = 1, j = mark[f][i]; i < m; i++, j = mark[j][i]){
        cout << " " << j;
    }
    cout << endl << ans << endl;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w+", stdout);
    while(cin >> n >> m){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                cin >> b[i][j];
            }
        }
        solve();
    }
    return 0;
}
