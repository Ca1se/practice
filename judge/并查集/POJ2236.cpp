#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1000 + 5;

pair<int, int> mp[maxn];
int toP[maxn], deep[maxn];
bool ok[maxn];
int N, d;

bool involve(pair<int, int>& a, pair<int, int>& b) {
    return ((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second) <= d * d);
}

int Find(int pos) {
    if(toP[pos] < 0 || !ok[toP[pos]])    return pos;
    return toP[pos] = Find(toP[pos]);
}

void Union(int p1, int p2) {
    int r1 = Find(p1), r2 = Find(p2);
    if(r1 == r2)    return;
    else if(deep[r1] <= deep[r2])   toP[r1] = r2;
    else    toP[r2] = r1;
    if(deep[r1] == deep[r2])    deep[r2]++;
}

int main() {
    memset(deep, 0, sizeof(deep));
    memset(toP, -1, sizeof(toP));
    memset(ok, 0, sizeof(ok));
    ios::sync_with_stdio(false);
    cin >> N >> d;
    for(int i = 0; i < N; i++) {
        cin >> mp[i].first >> mp[i].second;
    }
    
    char op;
    while(cin >> op) {
        if(op == 'O') {
            int pos;
            cin >> pos;
            pos--;
            ok[pos] = true;

            for(int i = 0; i < N; i++) {
                if(i == pos || !ok[i])  continue;
                if(involve(mp[i], mp[pos])) Union(i, pos);
            }
        }else {
            int pos1, pos2;
            cin >> pos1 >> pos2;
            if(Find(pos1 - 1) == Find(pos2 - 1)) {
                cout << "SUCCESS\n";
            }else {
                cout << "FAIL\n";
            }
        }
    }

    return 0;
}