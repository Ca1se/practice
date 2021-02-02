#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct Poll {
    ll x, y, z;
    ll to;
    inline void setp(ll x, ll y, ll z) {this->x = x;    this->y = y;     this->z = z;}
};
Poll mp[int(1e3 + 5)], b, t;
ll r, deep[int(1e3 + 5)];
inline bool involve(ll ax, ll ay, ll az, ll bx, ll by, ll bz) {
    return (ax - bx) * (ax - bx) + (ay - by) * (ay - by) + (az - bz) * (az - bz) <= r * r * 4;
}

ll Find(ll pos) {
    if(!mp[pos].to) return pos;
    ll p = Find(mp[pos].to);
    mp[pos].to = p;
    return p;
}

inline void Union(ll p1, ll p2) {
    ll r1 = Find(p1), r2 = Find(p2);
    if(r1 == r2)    return;
    else if(deep[r1] <= deep[r2]) mp[r1].to = r2;
    else    mp[r2].to = r1;
    if(deep[r1] == deep[r2]) {
        deep[r2]++;
    }
}
int main() {
    ll T, x, y, z;
    cin >> T;
    while(T--) {
        memset(mp, 0, sizeof(mp));
        memset(deep, 0, sizeof(deep));
        b.to = t.to = 0;
        ll n, h;
        cin >> n >> h >> r;
        for(ll i = 1; i < n + 1; i++) {
            cin >> x >> y >> z;
            mp[i].setp(x, y, z);
            for(ll j = 1; j < i; j++) {
                if(involve(mp[i].x, mp[i].y, mp[i].z, mp[j].x, mp[j].y, mp[j].z)) {
                    Union(i, j);
                }
            }
            if(mp[i].z <= r) {
                if(b.to) {
                    Union(b.to, i);                    
                }else {
                    b.to = Find(i);
                }
            }
            if(mp[i].z + r >= h) {
                if(t.to) {
                    Union(t.to, i);
                }else {
                    t.to = Find(i);
                }
            }
        }
        if(t.to && b.to && Find(t.to) == Find(b.to)) {
            cout << "Yes" << endl;
        }else {
            cout << "No" << endl;
        }
    }
    return 0;
}