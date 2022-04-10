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