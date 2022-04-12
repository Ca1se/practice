#include <cstdio>
#include <unordered_map>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 200 + 5;

unordered_map<int, int> ind;
int n, k, ind1, ind2, minc = 0x3f3f3f3f, num = 0, maxh = -1;
int tmp, tmp1;
int name[maxn];
int happy[maxn];
int hadc[maxn];
int cost[maxn][maxn];
bool vis[maxn] = {};
vector<int> path;
vector<int> ans;

char rom[] = "ROM";


void dfs(int pos, int c, int h) {
    if(name[pos] == *(int*) rom) {
        if(c < minc) {
            minc = c, num = 1, maxh = h, ans = path;
        }else if(c == minc) {
            num++;
            if(h > maxh)
                maxh = h, ans = path;
            else if(h == maxh && path.size() < ans.size()) {
                ans = path;
            }
        }
        return;
    }

    if(c > hadc[pos]) return;
    hadc[pos] = c;
    
    for(int i = 1; i < n; i++) {
        if(!vis[i] && cost[pos][i] < 0x3f3f3f3f) {
            vis[i] = true;
            path.push_back(i);
            dfs(i, c + cost[pos][i], h + happy[i]);
            path.pop_back();
            vis[i] = false;
        }
    }
}

int main() {
    memset(cost, 0x3f, sizeof cost);
    memset(hadc, 0x3f, sizeof hadc);
    scanf("%d %d %s", &n, &k, (char*) &tmp);
    ind[tmp] = 0;
    name[0] = tmp;
    for(int i = 1; i < n; i++) {
        scanf("%s %d", (char*) &tmp, happy + i);
        ind[tmp] = i;
        name[i] = tmp;
    }

    for(int i = 0; i < k; i++) {
        scanf("%s %s", (char*) &tmp, (char*) &tmp1);
        ind1 = ind[tmp], ind2 = ind[tmp1];
        scanf("%d", &cost[ind1][ind2]);
        cost[ind2][ind1] = cost[ind1][ind2];
    }

    dfs(0, 0, 0);

    printf("%d %d %d %d\n", num, minc, maxh, maxh / ans.size());
    printf("%s", (char*) &name[0]);
    for(int pos: ans) {
        printf("->%s", (char*) &name[pos]);
    }
    
    return 0;
}
