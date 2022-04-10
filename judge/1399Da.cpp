#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
const int maxn = 2 * 1e5 + 5;
int n, mark[maxn];
char s[maxn], * p;
stack<int> q0, q1;
void solve() {
    memset(mark, 0, sizeof(mark));
    while (p != s + n) {
        if (*p == '0' && q1.size()) {
            mark[p - s] = q1.top();
            q0.push(mark[p - s]);
            q1.pop();
        }
        else if (*p == '1' && q0.size()) {
            mark[p - s] = q0.top();
            q1.push(mark[p - s]);
            q0.pop();
        }
        else {
            int t = q0.size() + q1.size() + 1;
            mark[p - s] = t;
            if (*p == '0')   q0.push(t);
            else    q1.push(t);
        }
        p++;
    }
}
void clr() {
    while (!q0.empty())
    {
        q0.pop();
    }
    while(!q1.empty()){
        q1.pop();
    }
    
}
int main() {
    ios::sync_with_stdio(false);
    //freopen("test.in", "r", stdin);
    int test;
    cin >> test;
    for (int i = 0; i < test; i++) {
        clr(); p = s;
        cin >> n >> s;
        solve();
        cout << q0.size() + q1.size() << '\n' << mark[0];
        for (int i = 1; i < n; i++)  cout << ' ' << mark[i];
        cout << '\n';
    }
}