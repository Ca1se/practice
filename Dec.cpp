#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 1000 + 5;
int w[maxn][maxn];
int esprime(int a, int b)  {
    int t;
    while(t = a % b){
        a = b;
        b = t;
    }
    return b == 1 ? 1 : 0;
}

int solve(int a, int b) {
    if(w[a][b] != 0)   return w[a][b];
    int m = 0;
    if(a != 1)  m = solve(a - 1, b);
    if(b != 1)  m = max(m, solve(a, b - 1));
    return w[a][b] = w[b][a] = esprime(a, b) ? m + 1 : m;
}

/*
void solve() {
    for(int i = 1; i <= 1000; i++){
        for(int j = 1; j <= 1000; j++){
            if(w[i][j])  continue;
            w[i][j] = w[j][i] = esprime(i, j) + max(w[i - 1][j], w[i][j - 1]);
        }
    }
} */
int main() {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    int test, a, b;
    scanf("%d", &test);
    memset(w, 0, sizeof(w));
    w[1][1] = 1;
    solve(1000, 1000);
    for(int k=0; k < test; k++){
        scanf("%d%d", &a, &b);
        printf("%d\n", w[a][b]);
    }
    return 0;
}