#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

const int maxn = 2 * 1e5 + 5;
vector<int> edge[maxn];
vector<pair<int, int>> und;
vector<pair<int, int>> ord;
set<int> s;
queue<int> q;
int idx[maxn];
int ind[maxn];

int main() {
    int t, n, m, cnt = 0, type, from, to;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        cnt = 0;
        memset(idx, -1, (n + 1) * sizeof(int));
        memset(ind, 0, (n + 1) * sizeof(int));
        for(int i = 1; i <= n; i++) edge[i].clear();
        und.clear();
        ord.clear();
        s.clear();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &type, &from, &to);
            if(type) {
                ord.emplace_back(from, to);
                edge[from].push_back(to);
                s.insert(from);
                s.insert(to);
                ind[to]++;
            }else {
                und.emplace_back(from, to);
            }
        }
        for(int i: s) {
            if(ind[i] == 0) q.push(i);
        }
        while(!q.empty()) {
            int p = q.front(); q.pop();
            idx[p] = cnt++;
            for(int it: edge[p]) {
                ind[it]--;
                if(ind[it] == 0) q.push(it);
            }
        }
        if(cnt == s.size()) {
            puts("YES");
            for(int i = 0; i < ord.size(); i++) {
                printf("%d %d\n", ord[i].first, ord[i].second);
            }
            for(int i = 0; i < und.size(); i++) {
                const auto& it = und[i];
                if(idx[it.first] == -1) {
                    idx[it.first] = cnt++;
                }
                if(idx[it.second] == -1) {
                    idx[it.second] = cnt++;
                }
                if(idx[it.first] < idx[it.second]) {
                    printf("%d %d\n", it.first, it.second);
                }else {
                    printf("%d %d\n", it.second, it.first);
                }
            }
        }else {
            puts("NO");
        }
    }
    return 0;
}
