#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
int mpot1, mpot2, res;
const string ops[6] = {"FILL(1)", "FILL(2)", "DROP(1)", "DROP(2)", "POUR(1,2)", "POUR(2,1)"};
struct OP { 
    OP(): pot1(0), pot2(0), ops() {}
    OP(int p1, int p2, const vector<int>& o): pot1(p1), pot2(p2), ops(o) {}
    int pot1;
    int pot2;
    vector<int> ops;
};

OP solve() {
    queue<OP> q;
    vector<int> r;
    vector<pair<int, int> > re;
    r.push_back(-1);
    q.push(OP(0, 0, r));
    while(!q.empty()) {
        OP t = q.front(); q.pop();
        if(t.pot1 == res || t.pot2 == res)  return t;
        if(re.size() && find(re.begin(), re.end(), make_pair(t.pot1, t.pot2)) != re.end())  continue;
        re.push_back(make_pair(t.pot1, t.pot2));
        if(t.pot1 != mpot1 && t.ops.back() != 2) {
            q.push(OP(mpot1, t.pot2, t.ops));
            q.back().ops.push_back(0);
        }
        if(t.pot2 != mpot2 && t.ops.back() != 3) {
            q.push(OP(t.pot1, mpot2, t.ops));
            q.back().ops.push_back(1);
        }
        if(t.pot1 && t.ops.back() != 0) {
            q.push(OP(0, t.pot2, t.ops));
            q.back().ops.push_back(2);
        }
        if(t.pot2 && t.ops.back() != 1) {
            q.push(OP(t.pot1, 0, t.ops));
            q.back().ops.push_back(3);
        }
        if(t.pot1 && t.pot2 != mpot2) {
            int pours = min(t.pot1, mpot2 - t.pot2);
            q.push(OP(t.pot1 - pours, t.pot2 + pours, t.ops));
            q.back().ops.push_back(4);
        }
        if(t.pot2 && t.pot1 != mpot1) {
            int pours = min(t.pot2, mpot1 - t.pot1);
            q.push(OP(t.pot1 + pours, t.pot2 - pours, t.ops));
            q.back().ops.push_back(5);
        }
    }
    return OP();
}

int main() {
    cin >> mpot1 >> mpot2 >> res;
    OP t = solve();
    if(!t.ops.size()) {
        cout << "impossible\n";
    }else {
        cout << t.ops.size() - 1 << endl;
        for(int i = 1; i < t.ops.size(); i++) {
            cout << ops[t.ops[i]] << endl;
        }
    }
    return 0;
}