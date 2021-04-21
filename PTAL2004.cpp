#include<bits/stdc++.h>
using namespace std;
int n;
bool isMirror = false;
vector<int> pre, post;
void getPost(int root, int tail) {
    int i = root + 1, j = tail;
    if(isMirror) {
        while(i <= tail && pre[i] >= pre[root]) i++;
        while(j > root && pre[j] < pre[root])   j--;
    }else {
        while(i <= tail && pre[i] < pre[root])   i++;
        while(j > root && pre[j] >= pre[root])  j--;
    }
    if(j != root)   getPost(root + 1, j);
    if(i != tail + 1)   getPost(i, tail);
    post.push_back(pre[root]);
}
int main() {
    cin >> n;
    int t;
    for(int i = 0; i < n; i++) {
        cin >> t;
        pre.push_back(t);
    }
    getPost(0, n - 1);
    if((int) post.size() != n) {
        post.clear();
        isMirror = true;
        getPost(0, n - 1);
    } 
    if((int) post.size() == n) {
        cout << "YES" << endl;
        cout << post[0];
        for(int i = 1; i < n; i++) {
            cout << " " << post[i];
        }
    }else {
        cout << "NO" << endl;
    }
    return 0;
}
