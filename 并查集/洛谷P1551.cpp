#include<bits/stdc++.h>
using namespace std;
int mp[5000] = {0};
int Find(int pos) {
    if(!mp[pos])    return pos;
    return Find(mp[pos]);
}
void Union(int a, int b) {
    int ra = Find(a), rb = Find(b);
    if(ra == rb)    return;
    mp[ra] = rb;
}
int main() {
    memset(mp, 0, sizeof(mp));
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