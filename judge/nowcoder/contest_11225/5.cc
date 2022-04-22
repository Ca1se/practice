#include <cstdio>
#include <map>
#include <utility>
using namespace std;
using ll = long long;
map<pair<ll, ll>, bool> mp;

ll aa, bb, tar;
bool dfs(ll a, ll b) {
    if(a == tar || b == tar) return true;
    if(mp[make_pair(a, b)]) return false;
    mp[make_pair(a, b)] = true;
    if(dfs(a & b, b)) return true;
    if(dfs(a & b, a)) return true;
    if(dfs(a | b, b)) return true;
    if(dfs(a | b, a)) return true;
    if(dfs(a ^ b, b)) return true;
    if(dfs(a ^ b, a)) return true;
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        scanf("%lld%lld%lld", &aa, &bb, &tar);
        if(dfs(aa, bb)) printf("Yes\n");
        else printf("No\n");
        mp.clear();
    }
}
