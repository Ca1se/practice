#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2 * 1e5 + 5;
int n, arr[maxn];
ll ans;
int main() {
    int test, m;
    cin >> test;
    while(test--){
        m = -1, ans = 0;
        cin >> n >> arr[0];
        for(int i = 1; i < n; i++){
            cin >> arr[i];
            if(m == -1 && arr[i] < arr[i - 1]){
                m = arr[i - 1];
            }else if(m != -1 && arr[i] > arr[i - 1] && arr[i] < m){
                ans += arr[i] - arr[i - 1];
            }else if(m != -1 && arr[i] >= m){
                ans += m - arr[i - 1];
                m = -1;
            }
        }
        if(m != -1)	ans += m - arr[n - 1];
		cout << ans << endl;
    }
	return 0;
}