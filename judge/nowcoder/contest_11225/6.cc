#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 5;
int n, u, v;
int val[maxn];
int cnt[maxn];
vector<int> path[maxn];

int ans;
void dfs(int pos, int pre) {
    for(int i = 0; i < path[pos].size(); i++) {
        if(path[pos][i] != pre) {
            dfs(path[pos][i], pos);
            int t = __gcd(val[pos], val[path[pos][i]]);
            val[pos] /= t;
            ans += cnt[t];
        }
    }
}

int main() {
    for(int i = 2; i < maxn; i++) {
        if(!cnt[i]) {
            cnt[i] = 1;
            for(int r = i + i; r < maxn; r += i) {
                int t = r;
                while(t % i == 0) t /= i, cnt[r]++;
            }
        }
    }
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", val + i);
    }
    for(int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        path[v].push_back(u);
        path[u].push_back(v);
    }
    dfs(1, -1);
    printf("%d\n", ans);
    return 0;
}
