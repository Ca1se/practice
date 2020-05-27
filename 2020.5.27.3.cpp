#include<iostream>
#include<cstring>
#include<set>
using namespace std;
char jar[21][21];//y,x
int direction[4][2] = { -1,0,0,1,1,0,0,-1 };//上,右,下,左
int n, m, t, ans = 0;
set<char> keybox;
bool judge(int y, int x) {
    if (!(x > -1 && x<m && y>-1 && y < n)) return false;
    //  ^   *   .   a   A   @
    if (jar[y][x] == '*')  return false;
    else if (jar[y][x] > 64 && jar[y][x] < 75) {
        if (keybox.find(jar[y][x]) != keybox.end())  return true;
        else   return false;
    }
    else    return true;
}
void findwayout(int y, int x, int cnt, int fdirection) {
    if (cnt >= t)  return;
    int bdc = 0, temp;
    if (jar[y][x] == '^') {
        if (!ans || cnt < ans)  ans = cnt;
    }
    else if (jar[y][x] > 96 && jar[y][x] < 107) {
        if (keybox.find(jar[y][x] - 32) == keybox.end()) {
            keybox.insert(jar[y][x] - 32);
            bdc++;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (i % 2 != fdirection % 2 || i == fdirection) {
            if (judge(y + direction[i][0], x + direction[i][1])) {
                findwayout(y + direction[i][0], x + direction[i][1], cnt + 1, i);
            }
            else   bdc++;
        }
        else   temp = i;
    }
    if (bdc == 4) {
        findwayout(y + direction[temp][0], x + direction[temp][1], cnt + 1, temp);
    }
}
int main() {
    ios::sync_with_stdio(false);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w+", stdout);
    int initpoint[2];//y,x
    while (cin >> n >> m >> t) {
        for (int i = 0; i < n; i++) {
            cin >> jar[i];
            if (strchr(jar[i], '@') != NULL) {
                initpoint[1] = strchr(jar[i], '@') - jar[i];
                initpoint[0] = i;
            }
        }
        findwayout(initpoint[0], initpoint[1], 0, -1);
        if (ans) cout << ans << endl;
        else    cout << -1 << endl;
        ans = 0;
        keybox.clear();
    }
    return 0;
}