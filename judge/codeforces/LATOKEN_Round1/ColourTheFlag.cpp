#include <bits/stdc++.h>
using namespace std;
const int maxn = 50 + 5;
char mp[2][maxn];
struct Status {
    Status() = default;
    Status(char mark, int x, int y): mark(mark), x(x), y(y) {}
    char mark;
    int x, y;
}status[maxn * maxn];
inline int mdist(const Status& t1, const Status& t2) {
    return abs(t1.x - t2.x) + abs(t1.y - t2.y);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t, n, m;
    cin >> t;
    while(t--) {
        int pos = 0, flagX, flagY;
        char tc, flagC = 0;
        cin >> n >> m;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> tc;
                if(tc == 'R' || tc == 'W') {
                    Status& s = status[pos++];
                    s.mark = flagC = tc;
                    s.x = flagX = j;
                    s.y = flagY = i;
                }
            }
        }
        for(int i = 0; i < pos; i++) {
            for(int k = i + 1; k < pos; k++) {
                Status& t1 = status[i], & t2 = status[k];
                if(t1.mark == t2.mark && (mdist(t1, t2) & 1) == 1) goto failed;
                else if(t1.mark != t2.mark && (mdist(t1, t2) & 1) == 0) goto failed;
            }
        }
        if(false) {
failed:
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        if(flagC == 0 || (flagC == 'R' && ((flagX + flagY) & 1) == 0) || 
                (flagC == 'W' && ((flagX + flagY) & 1) == 1)) {
            for(int i = 0; i < m; i++) {
                if(i & 1)   mp[0][i] = 'W', mp[1][i] = 'R';
                else        mp[0][i] = 'R', mp[1][i] = 'W';
            }
        }else {
            for(int i = 0; i < m; i++) {
                if(i & 1)   mp[0][i] = 'R', mp[1][i] = 'W';
                else        mp[0][i] = 'W', mp[1][i] = 'R';
            }
        }
        mp[0][m] = mp[1][m] = 0;
        for(int i = 0; i < n; i++) {
            cout << mp[i & 1] << '\n';
        }
    }
    return 0;
}
