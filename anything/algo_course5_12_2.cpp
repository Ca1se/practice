#include <bits/stdc++.h>
using namespace std;
const int maxn = 20 + 5;
bool mp[maxn][maxn] = {0};
int n, cnt = 0;
bool check(int x, int y) {
    //左上
    for(int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if(mp[j][i])    return false;
    }
    for(int i = x + 1, j = y - 1; i < n && j >= 0; i++, j--) {
        if(mp[j][i])    return false;
    }
    for(int i = y - 1; i >= 0; i--) {
        if(mp[i][x])    return false;
    }
    return true;
}
void solve(int h) {
    if(h < n) {
        for(int i = 0; i < n; i++) {
            if(check(i, h)) {
                mp[h][i] = true;
                solve(h + 1);
                mp[h][i] = false;
            }
        }
    }else {
        cout << "第" << ++cnt << "个解为:" << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(mp[i][j]) cout << " X";
                else cout << " O";
            }
            cout << endl;
        }
    } 
}
int main() {
    cin >> n;
    solve(0);
    return 0;
}
