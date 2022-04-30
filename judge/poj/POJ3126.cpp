#include<iostream>
#include<queue>
#include<cstring>
#include<cmath>
using namespace std;

bool isPrime[10000 + 5];
bool vis[10000 + 5];
int lhs, rhs;
inline void line() {
    int prime[10000] = {0};
    int pos = 0;
    for(int i = 2; i < 5000 + 1; i++) {
        if(!isPrime[i]) prime[pos++] = i;
        for(int j = 0; j < pos; j++) {
            if(i * prime[j] >= 10000)   break;
            isPrime[i * prime[j]] = true;
            if(!(i % prime[j])) break;
        }
    }
}

int solve() {
    queue<pair<int, int> > q;
    q.push(make_pair(lhs, 0));
    while(!q.empty()) {
        pair<int, int> it = q.front(); q.pop();
        if(it.first == rhs)    return it.second;
        for(int i = 1; i < 5; i++) {
            for(int j = 0; j < 10; j++) {
                int now = it.first / int(pow(10, i)) * int(pow(10, i)) + j * pow(10, i - 1) + it.first % int(pow(10, i - 1));
                if(now > 10000)
                    now++;
                if(now > 1000 && !isPrime[now] && !vis[now]) {
                    vis[now] = true;
                    q.push(make_pair(now, it.second + 1));
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    memset(isPrime, 0, sizeof(isPrime));
    line();
    int t;
    cin >> t;
    while(t--) {
        memset(vis, 0, sizeof(vis));
        cin >> lhs >> rhs;
        int r = solve();
        if(r != -1) {
            cout << r << '\n';
        }else{
            cout << "Impossible\n";
        }
    }
    return 0;
}