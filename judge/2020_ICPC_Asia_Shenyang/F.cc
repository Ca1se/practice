#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int pre_max[maxn], last_min[maxn], arr[maxn];
int main() {
    ios::sync_with_stdio(false);
    int n, ans = 1;
    cin >> n;
    cin >> arr[0];
    pre_max[0] = arr[0];
    for(int i = 1; i < n; i++) {
        cin >> arr[i];
        pre_max[i] = max(arr[i], pre_max[i - 1]);
    };
    last_min[n - 1] = arr[n - 1];
    for(int i = n - 2; i >= 0; i--) {
        last_min[i] = min(last_min[i + 1], arr[i]);
    }
    for(int i = 0; i < n - 1; i++) {
        if(pre_max[i] <= last_min[i + 1])    ans++;
    }
    cout << ans << "\n";
    return 0;
}
