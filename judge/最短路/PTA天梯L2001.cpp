#include<bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5;
int N, M, S, D;
int saveNum[maxn];
int maxSave[maxn];
int minRoute[maxn];
struct Edge {
    Edge(int f, int t, int d): from(f), to(t), dist(d) {}
    int from, to, dist;
};
struct Dijkstra {
    vector<Edge> edges; 
    vector<int> G[maxn];
    int p[maxn];
    bool vis[maxn];
    int d[maxn];
    typedef pair<int, int> pii;
    void add_edge(int from, int to, int dist) {
        G[from].push_back(edges.size());
        edges.emplace_back(from, to, dist);
    } 

    void dijkstra() {
        memset(vis, 0, sizeof vis);
        memset(d, 0x3f3f, sizeof d);
        memset(maxSave, 0, sizeof maxSave);
        memset(minRoute, 0, sizeof minRoute);
        priority_queue<pii , vector<pii>, greater<pii>> q;
        d[S] = 0;
        maxSave[S] = saveNum[S];
        minRoute[S] = 1;
        q.emplace(0, S);
        while(!q.empty()) {
            pii t = q.top(); q.pop();
            if(t.second == D)   break;
            else if(vis[t.second])   continue;
            vis[t.second] = true;
            for(int i = 0; i < (int) G[t.second].size(); i++) {
                Edge& edge = edges[G[t.second][i]];
                bool j1 = d[edge.to] > d[t.second] + edge.dist, j2 = d[edge.to] == d[t.second] + edge.dist, 
                                                j3 = maxSave[edge.to] < maxSave[t.second] + saveNum[edge.to];
                if(j1) {
                    minRoute[edge.to] = minRoute[t.second];
                    maxSave[edge.to] = maxSave[t.second] + saveNum[edge.to];
                    d[edge.to] = d[t.second] + edge.dist;
                    p[edge.to] = t.second;
                    q.emplace(d[edge.to], edge.to);
                }else if(j2) {
                    minRoute[edge.to] += minRoute[t.second];
                    if(j3) {
                        maxSave[edge.to] = maxSave[t.second] + saveNum[edge.to];   
                        p[edge.to] = t.second;
                    }
                    q.emplace(d[edge.to], edge.to);
                }
            }
        }
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M >> S >> D;
    for(int i = 0; i < N; i++)  cin >> saveNum[i];
    int from, to, dist;
    Dijkstra d;
    while(M--) {
        cin >> from >> to >> dist;
        d.add_edge(from, to, dist);
        d.add_edge(to, from, dist);
    }
    d.dijkstra();
    cout << minRoute[D] << " " << maxSave[D] << endl;
    stack<int> s;
    s.push(D);
    while(S != D) {
        s.push(d.p[D]);
        D = d.p[D];
    }
    cout << s.top();
    s.pop();
    while(!s.empty()) {
        cout << " " << s.top();
        s.pop(); 
    }
    cout << endl;
    return 0;
}