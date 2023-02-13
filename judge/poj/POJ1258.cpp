#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

struct Edge
{
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
    int u, v, w;
    bool operator<(const Edge& other) const
    {
        return w < other.w;
    }
};

static const int maxn = 100 + 5;
int n, ans;
std::vector<Edge> edges;
int root[maxn];

inline int Find(int p)
{
    return root[p] == -1 ? p : root[p] = Find(root[p]);
}

inline bool Union(int x, int y)
{
    int xx = Find(x), yy = Find(y);

    if(xx == yy)
        return false;
    
    root[xx] = yy;
    return true;
}

int main()
{
    int len;
    
    while(std::scanf("%d", &n) != EOF) {
        ans = 0;
        std::memset(root, 0xff, sizeof root);
        edges.clear();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                std::scanf("%d", &len);
                if(i < j)
                    edges.push_back(Edge(i, j, len));
            }
        }
        std::sort(edges.begin(), edges.end());
        for(int i = 0; i < edges.size(); i++) {
            const Edge& e = edges[i];
            if(Union(e.u, e.v))
                ans += e.w;
        }
        std::printf("%d\n", ans);
    }
    return 0;
}