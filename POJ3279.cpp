#include<iostream>
#include<cstring>
using namespace std;
const int MAX = 20;
int mp[MAX][MAX] = {0};
int mn[MAX][MAX], op[MAX][MAX];
int main() {
    int M, N;
    bool judge = false;
    cin >> M >> N;
    memset(mp, 0 ,sizeof(mp));
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> mp[i][j];
        }
    }
    for(int k = 0; k < (1 << N); k++) {
        memcpy(mn, mp, sizeof(mp));
        memset(op, 0, sizeof(op));
        for(int i = 0; i < N; i++) {
            //这里搜索顺序和操作顺序是反的，只有这样才能ac， 感觉是poj的测试数据有问题， 正反向的差别只有在输入数据是对称的情况下才体现
            //if(k >> i & 1)
            if((1 << i) & k) {
                op[0][i] = 1;
                mn[1][i + 1] = !mn[1][i + 1];
                mn[0][i + 1] = !mn[0][i + 1];
                mn[1][i] = !mn[1][i];
                mn[1][i + 2] = !mn[1][i + 2];
                mn[2][i + 1] = !mn[2][i + 1];
            }
        }
        for(int i = 1; i < M; i++) {
            for(int j = 0; j < N; j++) {
                if(mn[i][j + 1]) {
                    op[i][j] = 1;
                    mn[i + 1][j + 1] = !mn[i + 1][j + 1];
                    mn[i + 1][j] = !mn[i + 1][j];
                    mn[i + 1][j + 2] = !mn[i + 1][j + 2];
                    mn[i + 2][j + 1] = !mn[i + 2][j + 1];
                }
            }
        }
        int i;
        for(i = 1; i <=N; i++) {
            if(mn[M][i])    break;
        }
        if(i == N + 1) {
            judge = true;
            break;
        }
    }
    if(judge) {
        for(int i = 0; i < M; i++) {
            cout << op[i][0];
            for(int j = 1; j < N; j++) {
                cout << ' ' << op[i][j];
            }
            cout << '\n';
        }
    }else{
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}