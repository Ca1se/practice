#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

static const int maxn = 800;
static const int maxm = 1000 + 5;

struct Edge
{
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
    int u, v, w;
    bool operator<(const Edge& a) const
    {
        return w < a.w;
    }
};

int n, m;
std::pair<int, int> pos[maxn];
std::vector<Edge> edges;
int un[maxn];

inline int Find(int p)
{
    return un[p] == p ? p : un[p] = Find(un[p]);
}

inline bool Union(int x, int y)
{
    int xx = Find(x), yy = Find(y);

    if(xx == yy)
        return false;
    
    un[xx] = yy;
    return true;
}

inline int dist(int x, int y)
{
    std::pair<int, int> a = pos[x], b = pos[y];
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

int main()
{
    int x, y;
    std::scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        std::scanf("%d%d", &pos[i].first, &pos[i].second);
        un[i] = i;
        for(int j = 1; j < i; j++) {
            edges.push_back(Edge(i, j, dist(i, j)));
        }
    }
    std::scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        std::scanf("%d%d", &x, &y);
        Union(x, y);
    }
    std::sort(edges.begin(), edges.end());
    for(int i = 0; i < edges.size(); i++) {
        const Edge& e = edges[i];
        if(Union(e.u, e.v)) {
            std::printf("%d %d\n", e.u, e.v);
        }
    }
    
    return 0;
}