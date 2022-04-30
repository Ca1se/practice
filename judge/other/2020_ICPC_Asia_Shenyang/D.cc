#include <bits/stdc++.h>
using namespace std;
string que;
int n, cnt = 0;

void solve(int pos, int odd, int even, int num) {
    if(cnt == 100 || max(odd, even) > ceil((double) (n + 1) / 2)) return;
    if(pos == n) {
        cnt++;
        printf("%s\n", que.c_str());
        return;
    }
    que.push_back('b');
    if(num % 2) solve(pos + 1, odd + 1, even, num);
    else        solve(pos + 1, odd, even + 1, num);
    que.pop_back();
    que.push_back('r');
    if(num % 2) solve(pos + 1, odd, even + 1, num + 1);
    else        solve(pos + 1, odd + 1, even, num + 1);
    que.pop_back();
}

int main() {
    scanf("%d", &n);
    printf("%lld\n", (long long) ((n + 1) / 2) * ((int) ceil((double) (n + 1) / 2)));
    solve(0, 0, 1, 0);
    // bbbb
    return 0;
}
