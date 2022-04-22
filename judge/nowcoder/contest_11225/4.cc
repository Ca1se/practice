#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
using ll = long long;
int arr[maxn];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }
    sort(arr, arr + n);
    if(n == 2) {
        printf("%lld\n", (ll(arr[0]) + arr[1]) % mod);
    }else {
        ll res = arr[n / 2];
        int mp = (n / 2) + 1;
        int pp = (n / 2) - 1;
        for(int i = 1; i < n; i++) {
            if(i & 1) {
                res = (res + arr[pp--]) % mod;
            }else {
                res = (res * arr[mp++]) % mod;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
