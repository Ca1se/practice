/*
#include<queue>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int N, K;
int line[int(1e5) * 2];
struct Move {
    Move(int p, int s, int o): pos(p), step(s), op(o) {}
    int pos;
    int step;
    int op;
};

int solve() {
    memset(line, 0x3f, sizeof(line));
    queue<Move> q;
    q.push(Move(N, 0, -1));
    while(!q.empty()) {
        Move t = q.front(); q.pop();
        if(t.pos < 0 || t.step >= line[t.pos])   continue;
        line[t.pos] = t.step;
        if(t.pos == K)  return t.step;
        if(t.op != 1)   q.push(Move(t.pos - 1, t.step + 1, 0));
        if(t.op != 0 && t.pos < K)   q.push(Move(t.pos + 1, t.step + 1, 1));
        if(t.pos < K)   q.push(Move(t.pos * 2, t.step + 1, 2));
    }
    return 0;
}
int main() {
    cin >> N >> K;
    cout << solve() << endl;
    return 0;
}
*/

#include <cstdio>
#include <queue>

static const int maxn = 100000 + 5;
int n, k;
bool vis[maxn];

struct Status
{
    Status(int pos, int cnt): pos(pos), cnt(cnt) {}
    int pos;
    int cnt;
};

int main()
{
    scanf("%d%d", &n, &k);
    if(k <= n) {
        printf("%d\n", n - k);
        return 0;
    }
    std::queue<Status> q;
    q.push(Status(n, 0));
    vis[n] = true;
    while(!q.empty()) {
        Status now = q.front();
        q.pop();
        if(now.pos == k) {
            printf("%d\n", now.cnt);
            break;
        }
        if(now.pos < k) {
            int t1 = now.pos * 2;
            if(t1 <= 100000 && !vis[t1]) {
                vis[t1] = true;
                q.push(Status(t1, now.cnt + 1));
            }
            int t2 = now.pos + 1;
            if(t2 <= 100000 && !vis[t2]) {
                vis[t2] = true;
                q.push(Status(t2, now.cnt + 1));
            }
        }
        int t1 = now.pos - 1;
        if(t1 >= 0 && !vis[t1]) {
            vis[t1] = true;
            q.push(Status(t1, now.cnt + 1));
        }
    }
    return 0;
}
