#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
int arr[maxn];
int main() {
    int t, n;
    ll m, sum = 0, msum, r = 0, fmax;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%lld%d", &n, &m, arr);
        sum = msum = r = arr[0];
        if(r < 0)   r = 0;
        fmax = r;
        for(int i = 1; i < n; i++) {
            scanf("%d", arr + i);
            sum += arr[i];
            r += arr[i];
            if(r < 0)   r = 0;
            fmax = max(fmax, r);
            msum = max(msum, sum);
        }
        if(fmax >= m) {
            printf("1\n");
        }else {
            if(sum > 0) {
                printf("%lld\n", (long long)ceil(double(max(0ll, m - msum - r)) / sum) + 2);
            }else {
                int i = 0;
                for(; i < n; i++) {
                    r += arr[i];
                    if(r >= m)  break;
                    else if(r < 0)  r = 0;
                }
                printf("%d\n", (i != n ? 2 : -1));
            }
        }
    }
    return 0;
}
