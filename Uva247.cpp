#include<bits/stdc++.h>
using namespace std;
const int maxn = 25 + 5;
unordered_map<string, int> y;
unordered_map<int, string> x;
int mp[maxn][maxn];
bool vis[maxn];
int main() {
    int m, n;
    int cnt = 0;
    string chara, charb;
    while(cin >> m >> n && m && n) {
        memset(mp, 0, sizeof mp);
        memset(vis, 0, sizeof vis);
        for(int i = 0; i < maxn; i++)   mp[i][i] = 1;
        y.clear(); x.clear();
        for(int i = 0; i < n; i++) {
            cin >> chara >> charb;
            int siz = y.size();
            if(y.find(chara) == y.end())   y[chara] = ++siz, x[siz] = chara;
            if(y.find(charb) == y.end())   y[charb] = ++siz, x[siz] = charb;
            mp[y[chara]][y[charb]] = 1;
        } 
        for(int k = 1; k <= m; k++) {
            for(int i = 1; i <= m; i++) {
                for(int j = 1; j <= m; j++) {
                    mp[i][j] = (mp[i][j] || (mp[i][k] && mp[k][j]));
                }
            }
        }
        cout << "Calling circles for data set " << ++cnt << ":" << endl;
        for(int i = 1; i <= m; i++) {
            if(vis[i])  continue;
            vis[i] = true;
            cout << x[i];
            for(int j = i + 1; j <= m; j++) {
                if(vis[j] || !mp[i][j] || !mp[j][i])  continue;
                vis[j] = true;
                cout << ", " << x[j];
            }
            cout << endl;
        } 
    }
    return 0;
}