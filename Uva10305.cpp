#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 100 + 5;
int G[maxn][maxn];
int mark[maxn];
int topo[maxn], m ,n, t;

void dfs(int u) {
    mark[u] = 1;
    for(int i = 1; i <= n; i++){
        if(!mark[i] && G[u][i]) dfs(i);
    }
    topo[t--] = u;
}

void TopoOrder() {
    t = n - 1;
    for(int i = 1; i <= n; i++){
        if(!mark[i]) dfs(i);
    }
    cout << topo[0];
    for(int i = 1; i < n; i++) {
        cout << " " << topo[i];
    }
    cout << endl;
}

int main() {
    int u, v;
    while(cin >> n >> m && n) {
        memset(G, 0, sizeof(G));
        memset(mark, 0, sizeof(mark));
        for(int i = 0; i < m; i++){
            cin >> u >> v;
            G[u][v] = 1;
        }
        TopoOrder();
    }
    return 0;
}