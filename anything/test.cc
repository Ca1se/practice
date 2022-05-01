#include <cstdio>
#include <functional>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 500 + 5;
vector<int> edge[maxn];
vector<int> res;
priority_queue<int, vector<int>, greater<int>> q;
int ind[maxn];

int main() {
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        ind[v]++;
    }
    for(int i = 0; i < n; i++) {
        if(ind[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int p = q.top(); q.pop();
        res.push_back(p);
        for(auto it: edge[p]) {
            ind[it]--;
            if(ind[it] == 0) q.push(it);
        }
    }
    if(res.size() == n) {
        for(int i = 0; i < res.size(); i++) {
            printf("%d ", res[i]);
        }
        puts("");
    }else {
        puts("false");
    }
    return 0;
}
