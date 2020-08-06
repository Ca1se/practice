#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 2 * 1e5 + 5;
int n, mark[maxn];
char s[maxn], * p;
vector<int> q0, q1;
void solve() {
    memset(mark, 0, sizeof(mark));
    while (p != s + n) {
        if (*p == '0' && q1.size()) {
            mark[p - s] = q1.back();
            q0.push_back(mark[p - s]);
            q1.pop_back();
        }
        else if (*p == '1' && q0.size()) {
            mark[p - s] = q0.back();
            q1.push_back(mark[p - s]);
            q0.pop_back();
        }
        else {
            int t = q0.size() + q1.size() + 1;
            mark[p - s] = t;
            if (*p == '0')   q0.push_back(t);
            else    q1.push_back(t);
        }
        p++;
    }
}
int main() {
    ios::sync_with_stdio(false);
    //freopen("test.in", "r", stdin);
    int test;
    //q0.reserve(maxn), q1.reserve(maxn);
    cin >> test;
    for (int i = 0; i < test; i++) {
        q0.clear(); q1.clear(); p = s;
        cin >> n >> s;
        solve();
        cout << q0.size() + q1.size() << '\n' << mark[0];
        for (int i = 1; i < n; i++)  cout << ' ' << mark[i];
        cout << '\n';
    }
}