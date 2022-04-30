#include<iostream>
#include<queue>
using namespace std;
const int maxn = 2 * 1e5;
int n, mark[maxn];
char s[maxn], * p, t;
struct Seq {
    int id;
    char back;
    Seq(int id, char ch) : id(id), back(ch) {}
};
deque<Seq> q;
int check(char ch) {
    if (!q.size())   return 0;
    if (q.front().back != ch) {//0
        t = q.front().id;
        return 1;
    }
    else if (q.back().back != ch) {//1
        t = q.back().id;
        return 2;
    }
    return 0;
}
void solve() {
    int tmp;
    while (p != s + n) {
        tmp = check(*p);
        if (!tmp) {//没找到
            if (*p == '0')   q.push_front(Seq(q.size() + 1, '0'));
            else    q.push_back(Seq(q.size() + 1, '1'));
            mark[p - s] = q.size();
        }
        else if (tmp == 1) {//在前面找到了
            mark[p - s] = q.front().id;
            q.front().back = *p;
            q.push_back(q.front());
            q.pop_front();
        }
        else {
            mark[p - s] = q.back().id;
            q.back().back = *p;
            q.push_front(q.back());
            q.pop_back();
        }
        p++;
    }
}
int main() {
    ios::sync_with_stdio(false);
    //freopen("test.in", "r", stdin);
    int test;
    cin >> test;
    for (int i = 0; i < test; i++) {
        q.clear(); p = s;
        cin >> n >> s;
        solve();
        cout << q.size() << '\n' << mark[0];
        for (int i = 1; i < n; i++) {
            cout << ' ' << mark[i];
        }
        cout << '\n';
    }
}