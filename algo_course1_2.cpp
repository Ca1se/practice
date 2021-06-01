#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
int arr[maxn] = {0};
int n, m, s;
int solve(int l, int r) {
    int mid = (l + r) >> 1;
    if(arr[mid] == s) {
        return s;
    }else if(arr[mid] < s) {
        if(mid + 1 == r) {
            return arr[mid];
        }else {
            return solve(mid + 1, r);
        }
    }else {
        return solve(l, mid);
    }
}
int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> s;
        cout << solve(0, n) << endl;
    }
    return 0;
}
