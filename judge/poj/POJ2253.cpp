#include <cstdio>
#include <queue>
#include <cmath>
#include <cstring>

static const int maxn = 200 + 5;
int n;
bool vis[maxn];
std::pair<int, int> pos[maxn];

inline int distance(std::pair<int, int> a, std::pair<int, int> b)
{
    return static_cast<int>(sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second)) * 10000);
}

bool bfs(int dist)
{
    memset(vis, 0, sizeof vis);
    std::queue<int> q;
    q.push(0);
    vis[0] = true;
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        for(int i = 1; i < n; i++) {
            if(!vis[i] && ::distance(pos[now], pos[i]) <= dist) {
                if(i == 1) return true;
                q.push(i);
                vis[i] = true;
            }
        }
    }

    return false;
}

int main() {
    int cnt = 0;
    while(scanf("%d", &n) && n != 0) {
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &pos[i].first, &pos[i].second);
        }
        int minl = 0, maxl = ::distance(pos[0], pos[1]);
        while(minl != maxl) {
            int now = (minl + maxl) >> 1;
            if(bfs(now))
                maxl = now;
            else
                minl = now + 1;
        }
        printf("Scenario #%d\nFrog Distance = %.3f\n\n", ++cnt, static_cast<double>(minl) / 10000.0);
    }
    return 0;
}
