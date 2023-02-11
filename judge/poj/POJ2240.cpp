#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <queue>

static const int maxn = 30 + 5;
int n, m;
float worth[maxn];
bool vis[maxn];
int cnt[maxn];
std::map<std::string, int> nti;
struct Edge
{
    Edge(int to, float rate): to(to), rate(rate) {}
    int to;
    float rate;
};
std::vector<Edge> edges[maxn];

bool solve(int s)
{
    std::memset(worth, 0x00, sizeof worth);
    std::memset(vis, 0x00, sizeof vis);
    std::queue<int> q;
    q.push(s);
    worth[s] = 1.0f;
    vis[s] =  true;
    cnt[s] = 0;
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = false;
        for(int i = 0; i < edges[now].size(); i++) {
            Edge e = edges[now][i];
            if(worth[e.to] < worth[now] * e.rate) {
                worth[e.to] = worth[now] * e.rate;
                cnt[e.to] = cnt[now] + 1;
                if(cnt[e.to] >= n) return true;
                if(!vis[e.to]) {
                    q.push(e.to);
                    vis[e.to] = true;
                }
            }
        }
    }

    return false;
}

int main()
{
    int c = 0;
    char buf[64], buf1[64];
    float f;
    while(std::scanf("%d", &n) != EOF && n != 0) {
        nti.clear();
        for(int i = 0; i < maxn; i++)
            edges[i].clear();
        for(int i = 0; i < n; i++) {
            std::scanf("%s", buf);
            std::string t(buf);
            nti.insert(std::pair<std::string, int>(t, i));
        }
        std::scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            std::scanf("%s%f%s", buf, &f, buf1);
            edges[nti[std::string(buf)]].push_back(Edge(nti[std::string(buf1)], f));
        }
        for(int i = 0; i < n; i++) {
            if(solve(i)) {
                std::printf("Case %d: Yes\n", ++c);
                goto l;
            }
        }
        std::printf("Case %d: No\n", ++c);
        l:;
    }
    return 0;
}