#include <bits/stdc++.h>
using namespace std;

class AdjacencyList {
private:
    struct Node {
        Node(): next(nullptr) {}
        int to;
        Node* next;
    };

    void releaseTree() {

    }

    void createTree() {
        int m; //边的条数
        int f, t;
        cin >> m;
        size_t size = 0;
        while(m--) {
            cin >> f >> t;
            addEdge(f, t, size);
            addEdge(t, f, size);
        }
    }

    void addEdge(int f, int t, size_t& size) {
        size_t i = 0;
        for(; i < size; i++) {
            if(f == list[i].to) {
                Node* p = list + i;
                while(p->next != nullptr) p = p->next;
                p->next = new Node;
                p->next->to = t;
                break;
            }
        }
        if(i == size) {
            Node* p = list + size;
            p->to = f;
            p->next = new Node;
            p->next->to = t;
            size++;
        }
    }


    size_t n;
    Node* list;
public:
    AdjacencyList(size_t n): n(n), list(new Node[n]) {
        createTree();
    }

    virtual ~AdjacencyList() {
        if(list != nullptr) {
            releaseTree();
        }
    }

    void dfs() const {
        stack<int> s;
        map<int, bool> vis;
        s.push(list[0].to);
        vis[list[0].to] = true;
        while(!s.empty()) {
            int t = s.top(); s.pop();
            cout << t << " ";
            for(size_t i = 0; i < n; i++) {
                if(list[i].to == t) {
                    Node* p = list[i].next;
                    while(p != nullptr) {
                        if(!vis[p->to]) {
                            s.push(p->to);
                            vis[p->to] = true;
                        }
                        p = p->next;
                    }
                    break;
                }
            }
        }
        cout << endl;
    }

    void bfs() const {
        queue<int> q;
        map<int, bool> vis;
        q.push(list[0].to);
        vis[list[0].to] = true;
        while(!q.empty()) {
            int t = q.front(); q.pop();
            cout << t << " ";
            for(size_t i = 0; i < n; i++) {
                if(list[i].to == t) {
                    Node* p = list[i].next;
                    while(p != nullptr) {
                        if(!vis[p->to]) {
                            q.push(p->to);
                            vis[p->to] = true;
                        }
                        p = p->next;
                    }
                    break;
                }
            }
        }
        cout << endl;
    }
};

class AdjacencyMatrix {
private:
    const size_t n;
    vector<vector<int>> matrix;

    void initMatrix() {
        int m, f, t, l;
        cin >> m;
        while(m--) {
            cin >> f >> t >> l;
            matrix[f][t] = matrix[t][f] = l;
        }
    }
public:
    AdjacencyMatrix(int pn): n(pn), matrix(n, vector<int>(n, 0x3f3f3f3f)) {
        initMatrix();
    }

    int prim() const {
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<>> q;
        map<int, bool> vis;
        int sum = 0, cnt = 0;
        q.push({0, 1});
        while(!q.empty()) {
            pii t = q.top(); q.pop();
            if(vis[t.second])   continue;
            vis[t.second] = true;
            sum += t.first;
            if(++cnt == n - 1)  break;
            for(size_t i = 1; i < n; i++) {
                if(!vis[i] && matrix[t.second][i] != 0x3f3f3f3f) {
                    q.push({matrix[t.second][i], i});
                }
            }
        }
        return sum;
    }
};

int main() {
    /*
    int n;
    cin >> n;
    AdjacencyList a(n);
    a.dfs();
    a.bfs();
    */

    int n;
    cin >> n;
    AdjacencyMatrix m(n + 1);
    cout << m.prim();
    return 0;
}
