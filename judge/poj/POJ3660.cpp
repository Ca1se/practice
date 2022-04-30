#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 100 + 5;
bool mp[maxn][maxn];

int main() {
    ios::sync_with_stdio(false);
    memset(mp, 0, sizeof mp);
    int n, m;
    int a, b;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        mp[b][a] = true;
    }
    for(int i = 1; i <= n; i++) {
        mp[i][i] = true;
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                mp[i][j] = mp[i][j] || (mp[i][k] && mp[k][j]);
            }
        }
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        int j = 1;
        for(; j <= n; j++) {
            if(!(mp[i][j] || mp[j][i])) break;
        }
        if(j == n + 1)  cnt++;
    }
    cout << cnt << endl;
    return 0;
}