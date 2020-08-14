#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
ll R, G, B, p[200 + 5][200 + 5][200 + 5];
vector<int> r, b, g;
ll dp(int nr, int ng, int nb) {
    ll t = 0;
    if(p[nr][ng][nb])   return p[nr][ng][nb];
    if(nr - 1 >= 0 && ng - 1 >= 0) t = max(t, dp(nr - 1, ng - 1, nb) + r[nr - 1] * g[ng - 1]);
    if(ng - 1 >= 0 && nb - 1 >= 0) t = max(t, dp(nr, ng - 1, nb - 1) + g[ng - 1] * b[nb - 1]);
    if(nb - 1 >= 0 && nr - 1 >= 0) t = max(t, dp(nr - 1, ng, nb - 1) + r[nr - 1] * b[nb - 1]);
    return p[nr][ng][nb] = t;
}
int main() {
    //freopen("test.in", "r", stdin);
    memset(p, 0, sizeof(p));
    int t;
    cin >> R >> G >> B;
    for(int i = 0; i < R; i++){
        cin >> t;
        r.push_back(t);
    }
    sort(r.begin(), r.end(), [](int x, int y){ return x < y; });
    for(int i = 0; i < G; i++){
        cin >> t;
        g.push_back(t);
    }
    sort(g.begin(), g.end(), [](int x, int y){ return x < y; });
    for(int i = 0; i < B; i++){
        cin >> t;
        b.push_back(t);
    }
    sort(b.begin(), b.end(), [](int x, int y){ return x < y; });
    cout << dp(R, G, B) << endl;
}