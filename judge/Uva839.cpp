#include<bits/stdc++.h>
using namespace std;
bool solve(int& w) {
    int Wl, Dl, Wr, Dr;
    bool r1 = true, r2 = true;
    cin >> Wl >> Dl >> Wr >> Dr;
    if(!Wl) r1 = solve(Wl);
    if(!Wr) r2 = solve(Wr);
    w = Wl + Wr;
    return r1 && r2 && (Wl * Dl == Wr * Dr);
}
int main() {
    ios::sync_with_stdio(false);
    int n, w;
    cin >> n;
    while(n--) {
        cout << (solve(w) ? "YES\n": "NO\n");
        if(n)   cout << "\n";
    }
    return 0;
}