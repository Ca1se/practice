#include<iostream>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;

const int maxn = 50 + 5;
ll pre[maxn][maxn], past[maxn][maxn], K1[4][4], K[4][4];
int n;
void fuc() {
    for(int x = 1; x <= n; x++){
        for(int y = 1; y <= n; y++){
            past[x][y] = 0;
            for(int i = 1; i <= min(3, n - x + 1); i++){
                for(int j = 1; j <= min(3, n - y + 1); j++){
                    past[x][y] += pre[x + i - 1][y + j - 1] * K[i][j];
                }
            }
        }
    }
    bool judge = true;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(pre[i][j] != past[i][j]){
                judge = false;
                break;
            }
        }
    }
    if(judge){
        return;
    }else{
        memcpy(pre, past, sizeof(past));
        fuc();
    }
}
int main() {
    int test;
    cin >> test;
    while (test--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> pre[i][j];
            }
        }
        ll sum = 0;
        for(int i = 1; i <= 3; i++){
            for(int j = 1; j <= 3; j++){
                cin >> K1[i][j];
                sum += K1[i][j];
            }
        }
        for(int i = 1; i <= 3; i++){
            for(int j = 1; j <= 3; j++){
                K[i][j] = K1[i][j] / sum;
            }
        }
        fuc();
        for(int i = 1; i <= n; i++){
            cout << pre[i][1];
            for(int j = 2; j <= n; j++){
                cout << ' ' << pre[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}