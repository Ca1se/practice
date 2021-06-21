#include <bits/stdc++.h>
using namespace std;
const int maxn = 2 * 1e5 + 5;
long long a[maxn], tarr[maxn];
long long n, ll, rr;
long long get(int l, int r, int target) {
    int mid, t1 = -1, t2, i = l, j = r - 1;
    while(i <= j) {
        mid = (i + j) >> 1;
        long long tr = a[mid] + a[target];
        if(tr <= rr && tr >= ll && (j == mid || a[mid + 1] + a[target] > rr)) {
            t1 = mid;
            break;
        }else if(tr > rr) j = mid - 1;
        else i = mid + 1;
    }
    i = l, j = r - 1;
    while(i <= j) {
        mid = (i + j) >> 1;
        long long tr = a[mid] + a[target];
        if(tr >= ll && tr <= rr && (i == mid || a[mid - 1] + a[target] < ll)) {
            t2 = mid;
            break;
        }else if(tr < ll) i = mid + 1;
        else j = mid - 1;
    }
    return t1 == -1 ? 0 : t1 - t2 + 1;
}

long long solve(int l, int r) {
    if(r - l > 1) {
        int mid = (l + r) >> 1, pos = l;
        long long sum = solve(l, mid) + solve(mid, r);
        int i = l, j = mid;
        while(i < mid || j < r) {
            if(i >= mid || (j < r && a[i] > a[j])) {
                sum += get(i, mid, j);
                tarr[pos++] = a[j++];
            }else {
                sum += get(j, r, i);
                tarr[pos++] = a[i++];
            }
        }
        for(int k = l; k < r; k++) {
            a[k] = tarr[k];
        }
        return sum;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        cin >> n >> ll >> rr;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << solve(0, n) << endl;
    }
    return 0;
}
