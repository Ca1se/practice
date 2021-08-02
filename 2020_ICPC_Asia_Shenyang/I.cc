#include <bits/stdc++.h>
using namespace std;
int main() {
    long long H, M, A, ans = 0, pre = 0;
    cin >> H >> M >> A;
    for(int i = 0; i < H; i++) {
        long long jfront, jback;
        double f = ((double)i * M - A) / (H - 1), b = ((double)i * M + A) / (H - 1);
        jfront = max((long long) ceil(f), (long long) 0);
        if(pre && !jfront)  jfront++;
        jback = min((long long) b, M);
        if(jback == M)  pre = 1;
        else pre = 0;
        ans += max(jback - jfront + 1, (long long) 0);
    }
    cout << ans - 1 << "\n";
    return 0;
}

