#include<iostream>
#include<string>
#include<cstring>
using namespace std;
const int maxn = 200 + 5;
char s[maxn][maxn];
void solve(int r, int c) {
    cout << s[r][c] << '(';
    if(s[r + 1][c] == '|'){
        for(int i = 0; i < strlen(s[r + 2]); i++){
            if(s[r + 2][i] == '-'){
                if(s[r + 3][i] != ' ' && s[r + 3][i] != '#' && s[r + 3][i] != 0){
                    solve(r + 3, i);
                }
            }else if(i != 0 && s[r + 2][i - 1] == '-'){
                memset(s[r + 2], 32, i);
                break;
            }
        }
    }
    cout << ')';
}
int main() {
    //freopen("test.in", "r", stdin);
    int test, cnt, c;
    cin >> test;
    getchar();
    while (test--){
        cnt = 0, c = 0;
        memset(s, 0, sizeof(s));
        while(gets(s[cnt]) && s[cnt++][0] != '#');
        while(s[0][c++] == ' ' || s[0][c - 1] == '#');
        cout << '(';
        if(cnt != 1){
            solve(0, c - 1);
        }
        cout << ')' << '\n';
    }
    return 0;
}