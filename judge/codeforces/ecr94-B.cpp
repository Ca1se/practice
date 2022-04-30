#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll p, f, cnts, cntw, s, w;
ll solve() {
    ll ans = 0, tp;
    for(int i = 0; i <= min(p / s, cnts); i++){
        ll pw = min((p - i * s) / w, cntw);//p中w的数量
        ll fs = min(cnts - i, f / s);
        ll fw = min((f - fs * s) / w, cntw - pw);
        ans = max(ans, pw + fs + fw + i);
    }
    return ans;
}
int main() {
    int test;
    cin >> test;
    while(test--){
        cin >> p >> f >> cnts >> cntw >> s >> w;
        if(s > w){
            swap(s, w);
            swap(cnts, cntw);
        }
        cout << solve() << endl;
    }
}