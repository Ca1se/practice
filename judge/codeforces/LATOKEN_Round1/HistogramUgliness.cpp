#include<bits/stdc++.h>
using namespace std;
const int maxn = 4 * 1e5 + 5;
int arr[maxn];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t, n;
    cin >> t;
    while(t--) {
        long long op = 0;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        if(n == 1) {
            cout << arr[0] << "\n";
        }else if(n == 2) {
            cout << min(arr[0], arr[1]) * 2 + abs(arr[0] - arr[1]) << "\n";
        }else {
            if(arr[0] > arr[1]) {
                op += arr[0] - arr[1];
                arr[0] = arr[1];
            }
            if(arr[n - 1] > arr[n - 2]) {
                op += arr[n - 1] - arr[n - 2];
                arr[n - 1] = arr[n - 2];
            }
            for(int i = 1; i < n - 1; i++) {
                if(arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
                    int m = max(arr[i - 1], arr[i + 1]);
                    op += arr[i] - m;
                    arr[i] = m;
                }
            }
            for(int i = 0; i < n - 1; i++) {
                op += abs(arr[i] - arr[i + 1]);
            }
            cout << op + arr[0] + arr[n - 1] << "\n";
        }
    }

    return 0;
}
