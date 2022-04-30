#include<iostream>
#include<queue>
#include<vector>
#define ll long long
#define pll pair<ll, ll>
using namespace std;
const int maxn = 1e5 + 5;
int n;
ll S, c;
vector<int> G[maxn];
struct cmp {
    bool operator() (const pll& x, const pll& y) const {
        return (x.first - x.first / 2) * x.second < (y.first - y.first / 2) * y.second;
    }
};
priority_queue<pll, vector<pll>, cmp> q;

struct Edge {
    int u, v, w;
}edge[maxn];

void clr() {
    c = 0;
    while(!q.empty()){
        q.pop();
    }
    for(int i = 0; i < n + 1; i++){
        G[i].clear();
    }
}

ll dfs(int s, int pre) {
    ll t, times, sum = 0;
    for(int i = 0; i < G[s].size(); i++){
        t = G[s][i];
        if(edge[t].u == pre || edge[t].v == pre)    continue;
        times = dfs(edge[t].u + edge[t].v - s, s);
        q.push(make_pair(edge[t].w, times));
        c += edge[t].w * times;
        sum += times;
    }
    return sum == 0 ? 1 : sum;
}

ll solve() {
    ll ans = 0;
    dfs(1, -1);
    while(c > S){
        ans++;
        pll t = q.top();
        c -= (t.first - t.first / 2) * t.second;
        t.first = t.first / 2;
        q.push(t);
        q.pop();
    }
    return ans;
}
int main() {
    //freopen("test.in", "r", stdin);
    int test;
    cin >> test;
    for(int i = 0; i < test; i++){
        clr();
        cin >> n >> S;
        for(int j = 0; j < n - 1; j++){
            cin >> edge[j].u >> edge[j].v >> edge[j].w;
            G[edge[j].u].push_back(j);
            G[edge[j].v].push_back(j);
        }
        cout << solve() << endl;
    }
    return 0;
}