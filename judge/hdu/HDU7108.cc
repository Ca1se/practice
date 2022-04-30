#include <bits/stdc++.h>
using namespace std;
using ll = long long;
map<int, map<int, int>> arr;
int main() {
    int t, n;
    char ch;
    scanf("%d", &t);
    while(t--) {
        arr.clear();
        scanf("%d", &n);
        ll ans = 0;
        int x = n, y = n;
        arr[y][x]++;
        for(int i = 0; i < n; i++) {
            scanf(" %c", &ch);
            if(ch == 'U') y--;
            else if(ch == 'R') x++;
            else if(ch == 'D') y++;
            else if(ch == 'L') x--;
            ans += arr[y][x];
            arr[y][x]++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
