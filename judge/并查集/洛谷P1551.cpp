//路径压缩与按秩合并
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5000 + 5;
int mp[maxn] = {0};
int deep[maxn] = {0};
inline int Find(int pos) {
    if(!mp[pos])    return pos;
    int p = Find(mp[pos]);
    mp[pos] = p;
    return p;
}
inline void Union(int a, int b) {
    int ra = Find(a), rb = Find(b);
    if(ra == rb)    return;
    else if(deep[ra] <= deep[rb]) {
        mp[ra] = rb;
    }else {
        mp[rb] = ra;
    }
    if(deep[ra] == deep[rb])    deep[rb]++;
}
int main() {
    int n, m, p, a, b;
    cin >> n >> m >> p;
    while(m--) {
        cin >> a >> b;
        Union(a, b);
    }
    while(p--) {
        cin >> a >> b;
        if(Find(a) == Find(b)) {
            cout << "Yes" << endl;
        }else {
            cout << "No" << endl;
        }
    }
    return 0;
}