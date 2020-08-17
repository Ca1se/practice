#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2 * 1e5 + 5;
ll n, k, arr[maxn], maxx, minn;
int main() {
    ios::sync_with_stdio(false);
    int test;
    cin >> test;
    while(test--){
        cin >> n >> k;
        cin >> arr[0];
        maxx = minn = arr[0];
        for(int i = 1; i < n; i++){
            cin >> arr[i];
            maxx = max(maxx, arr[i]);
            minn = min(minn, arr[i]);
        }
        if(k & 1){
            cout << maxx - arr[0];
            for(int i = 1; i < n; i++){
                cout << " " << maxx - arr[i];
            }
        }else{
            cout << arr[0] - minn;
            for(int i = 1; i < n; i++){
                cout << " " << arr[i] - minn;
            }
        }
        cout << endl;
    }
}