#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 500 + 5;
priority_queue<int, vector<int>, greater<int>> q;
vector<int> edges[maxn];
vector<int> topo;
int ind[maxn];

int main() {
    int n, m, u, v;
    while(~scanf("%d%d", &n, &m)) {
        memset(ind, 0, (n + 1) * sizeof(int));
        for(int i = 0; i < n + 1; i++) edges[i].clear();
        topo.clear();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            edges[u].push_back(v);
            ind[v]++;
        }
        for(int i = 1; i <= n; i++) {
            if(!ind[i]) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int p = q.top(); q.pop();
            topo.push_back(p);
            for(int it: edges[p])
            if(--ind[it] == 0) {
                q.push(it);
            }
        }
        printf("%d", topo.front());
        for(int i = 1; i < topo.size(); i++) {
            printf(" %d", topo[i]);
        }
        puts("");
    }
    return 0;
}
