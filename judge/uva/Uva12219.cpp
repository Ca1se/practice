#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#include<string>
#include<queue>
using namespace std;
const int maxn = 50000 * 6 + 5;
struct Node {
    string s;
    int l = 0, r = 0;
    bool operator< (const Node& x) const {
        if (this->s != x.s)  return this->s < x.s;
        else {
            if (this->l != x.l)  return this->l < x.l;
            else    return this->r < x.r;
        }
    }
}node[maxn];
map<Node, int> tree, rtree;
queue<int> m[maxn];
int n, p;
char s[maxn], * r;

void mark() {
    int c = strlen(s);
    while (r != s + c) {
        if (*r == '(')   p++;
        else if (*r == ')') p--;
        else if (*r == ',')  m[p].push(r - s);
        r++;
    }
}
int build_tree(int x, int y, int step) {
    int u, c1, c2;
    Node tmp;
    if (s[y - 1] != ')') {//只有一个节点
        u = tree.size() + 1;
        tmp.s.assign(s + x, y - x);
        if (tree.find(tmp) == tree.end()) {
            tree[tmp] = u;
            node[u] = tmp;
        }
        return tree[tmp];
    }
    c2 = m[step].front();
    c1 = strchr(s + x, '(') - s;
    m[step].pop();
    tmp.l = build_tree(c1 + 1, c2, step + 1);
    tmp.r = build_tree(c2 + 1, y - 1, step + 1);
    u = tree.size() + 1;
    tmp.s.assign(s + x, c1 - x);
    if (tree.find(tmp) == tree.end()) {
        tree[tmp] = u;
        node[u] = tmp;
    }
    return tree[tmp];
}

void correct_tree(int u) {
    if (rtree.find(node[u]) == rtree.end()) {
        rtree[node[u]] = rtree.size() + 1;
        if (node[u].l) {
            correct_tree(node[u].l);
            correct_tree(node[u].r);
        }
    }
}

void print_tree(int u) {
    if (tree[node[u]] != -1) {
        tree[node[u]] = -1;
        cout << node[u].s;
        if (node[u].l) {//母节点
            cout << "(";
            print_tree(node[u].l);
            cout << ",";
            print_tree(node[u].r);
            cout << ")";
        }
    }
    else {
        cout << rtree[node[u]];
    }
}

int main() {
    ios::sync_with_stdio(false);
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    cin >> n;
    for (int k = 0; k < n; k++) {
        p = -1, r = s;
        tree.clear();
        rtree.clear();
        cin >> s;
        mark();
        build_tree(0, strlen(s), 0);
        correct_tree(tree.size());
        print_tree(tree.size());
        cout << endl;
    }
    return 0;
}