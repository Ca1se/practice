#include<iostream>
using namespace std;
const int maxn = 5 * 1e4 + 5;
int a[maxn], n, ans[3] = {1, 2};
bool solve() {
    for(int i = 2; i < n; i++){
        if(a[0] + a[1] <= a[i]){
            ans[2] = i + 1;
            return true;
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    //freopen("test.in", "r", stdin);
    int test;
    cin >> test;
    while(test--){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(solve()) cout << ans[0] << " " << ans[1] << " " << ans[2] << endl;
        else    cout << -1 << endl;
    }
}