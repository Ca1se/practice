#include<bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int n, m, topo[maxn], G[maxn][maxn], mark[maxn], pos;

void dfs(int c) {
    mark[c] = 1;
    for(int i = 1; i <= n; i++){
        if(!mark[i] && G[c][i]){
            dfs(i);
        }
    }
    topo[pos--] = c;
}

void topotrans() {
    pos = n - 1;
    memset(mark, 0, sizeof(mark));
    memset(topo, 0, sizeof(topo));
    for(int i = 1; i <= n; i++){
        if(!mark[i])
            dfs(i);
    }
    cout << topo[0];
    for(int i = 1; i < n; i++){
        cout << " " << topo[i];
    }
    cout << endl;
}

int main() {
    int t1, t2;
    while (cin >> n >> m && n){
        memset(G, 0, sizeof(G));
        for(int i = 0; i < m; i++){
            cin >> t1 >> t2;
            G[t1][t2] = 1;
        }
        topotrans();
    }
    return 0;
}