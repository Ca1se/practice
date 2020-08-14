#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 50 + 5;
const int maxt = 50 * 180 + 5;
int n, t, pn[maxn][maxt], pt[maxn][maxt], songs[maxn];
void solve() {
    memset(pn, 0, sizeof(pn));
    memset(pt, 0, sizeof(pt));
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= t - 1; j++){
            pn[i][j] = (i == 1 ? 0 : pn[i - 1][j]);
            pt[i][j] = (i == 1 ? 0 : pt[i - 1][j]);
            if(j >= songs[i]){
                if(pn[i][j] < pn[i - 1][j - songs[i]] + 1){
                    pn[i][j] = pn[i - 1][j - songs[i]] + 1;
                    pt[i][j] = pt[i - 1][j - songs[i]] + songs[i];
                }else if(pn[i][j] == pn[i - 1][j - songs[i]] + 1 && pt[i][j] < pt[i - 1][j - songs[i]] + songs[i]){
                    pt[i][j] = pt[i - 1][j - songs[i]] + songs[i];
                }
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    /*freopen("test.in", "r", stdin);
    freopen("test.out" ,"w+", stdout);*/
    int test;
    cin >> test;
    for(int i = 0; i < test; i++){
        cin >> n >> t;
        for(int j = 1; j <= n; j++){
            cin >> songs[j];
        }
        t = min(t, 50 * 180 + 1);
        solve();
        cout << "Case " << i + 1 << ": " << pn[n][t - 1] + 1 << " " << pt[n][t - 1] + 678 << endl;
    }
}