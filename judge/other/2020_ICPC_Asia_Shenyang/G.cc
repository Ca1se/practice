#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
int arr[maxn];
int main() {
    int n, m;
    cin >> n >> m;
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n, [](int x, int y) {
        return x > y;
    });
    for(int i = 0; i < m; i++) {
        ans += arr[i];
    }
    cout << ans << "\n";
    return 0;
}
