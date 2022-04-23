#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int maxl = 1e7 + 5;
int l[maxl] = {}, r[maxl] = {};
ll lv[maxl] = {}, rv[maxl] = {};
int main() {
    int n, len, la, ra, maxr = 0;
    scanf("%d%d", &n, &len);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &la, &ra);
        l[la]++, r[ra]++;
        lv[la] += i, rv[ra] += i;
        maxr = max(maxr, ra);
    }
    ll hap = 0, val = 0;
    for(int i = 1; i <= len; i++) {
        hap += l[i];
        val += lv[i];
    }
    ll max_hap = hap, max_val = val, cnt = 1;
    for(int i = 2; i <= maxr; i++) {
        hap -= r[i - 1], val -= rv[i - 1];
        hap += l[i + len - 1], val += lv[i + len - 1];
        if(hap > max_hap) max_hap = hap, max_val = val, cnt = 1;
        else if(hap == max_hap) {
            if(val > max_val) max_val = val, cnt = 1;
            else if(val == max_val) cnt++;
        }
    }
    printf("%lld\n", cnt);
    return 0;
}
