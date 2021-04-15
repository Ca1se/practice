#include<bits/stdc++.h>
using namespace std;
const int maxs = 0b111111111111111 + 5;
const int maxn = 15 + 5;
int n, Num;
int dp[maxs], deadLine[maxn], need[maxn], path[maxs];
string names[maxn];
int main() {
    ios::sync_with_stdio(false);
    stack<int> s;
    cin >> Num;
    while(Num--) {
        memset(dp, 0x3f3f, sizeof dp);
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> names[i] >> deadLine[i] >> need[i];
        }
        dp[0] = 0;
        for(int i = 1; i <= (1 << n) - 1; i++) {
            int cnt = 0, sNeed = 0;
            for(int k = 0; k < n; k++) {
                if((1 << k) & i) {
                    cnt++;
                    sNeed += need[k];
                }
            }
            for(int k = n - 1; k >= 0; k--) {
                if((1 << k) & i) {
                    int t = dp[i - (1 << k)] + (sNeed > deadLine[k] ? sNeed - deadLine[k] : 0);
                    if(dp[i] > t) {
                        dp[i] = t;
                        path[i] = i - (1 << k); 
                    }
                }
            }          
        }
        int now = (1 << n) - 1;
        path[0] = 0;
        cout << dp[now] << endl;
        while(path[now] != now) {
            int t = now - path[now];
            for(int i = 0; i < n; i++) {
                if((1 << i) & t) {
                    s.push(i);
                    break;
                }
            }
            now = path[now];
        }
        while(!s.empty()) {
            cout << names[s.top()] << endl;
            s.pop();
        }
    }
    return 0;
}