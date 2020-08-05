#include<cstdio>
#include<cstring>
const int maxn = 100 + 5;
char pic[maxn][maxn];
int mark[maxn][maxn], m, n;

void dfs(int i, int j){
    if((i < 0 || i >= m) || (j < 0 || j >= n))  return;//超出范围
    if(mark[i][j] != 0 || pic[i][j] == '*') return;
    mark[i][j] = 1;
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i - 1, j + 1);
    dfs(i + 1, j + 1);
    dfs(i + 1, j - 1);
    dfs(i - 1, j - 1);
}

int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    while (scanf("%d%d", &m, &n) == 2 && m && n){
        int cnt = 0;
        memset(mark, 0, sizeof(mark));
        for(int i = 0; i < m; i++){
            scanf("%s", pic[i]);
        }
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(mark[i][j] == 0 && pic[i][j] == '@'){
                    dfs(i, j);
                    cnt++;
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}