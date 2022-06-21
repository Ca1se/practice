#include <cstdio>
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 100000 + 5;
int in[maxn];

vector<int> path[maxn];
int val[maxn];

struct E {
    int p;
    bool operator< (const E& e) const noexcept {
        return val[this->p] > val[e.p];
    }
};

int main() {
    int n, k, u, v;
    memset(val, 0, sizeof val);
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        path[u].push_back(v);
        path[v].push_back(u);
        in[u]++;
        in[v]++;
    }
    priority_queue<E> q;

    for(int i = 1; i <= n; i++) {
        if(in[i] == 1) {
            val[i]++;
            q.push(E{ i });
        }
    }
    
    int ans = 0;
    for(int i = 0; i < n - k; i++) {
        int tp = q.top().p; q.pop();
        ans = max(ans, val[tp]);
        for(int r = 0; r < path[tp].size(); r++) {
            int to = path[tp][r];
            val[to] = max(val[to], val[tp] + 1);
            if(--in[to] == 1) q.push(E{ to });
        }
    }
    printf("%d\n", ans);

    return 0;
}
