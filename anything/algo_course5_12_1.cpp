#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;

int n = 4, W = 31;
int w[] = {0, 11, 13, 24, 7};
int count = 0;

void dfs(int i, int tw, int rw, int* x) {
    if(i > n) {
        if(tw == W) {
            cout << "第" << ++::count << "个解:" << endl;
            cout << "/t选取的数为";
            for(int r = 1; r <= n; r++) {
                if(x[r])    cout << " " << w[r]; 
            }
            cout << endl;
        }
    }else {
        if(tw + w[i] <= W) {
            x[i] =1;
            dfs(i + 1, tw + w[i], rw - w[i], x);
        }
        if(tw + rw - w[i] >= W) {
            x[i] = 0;
            dfs(i + 1, tw, rw - w[i], x);
        }
    }
}

int main() {
    int x[maxn];
    int rw = 0;
    for(int i = 1; i <= n; i++) {
        rw += w[i];
    }
    dfs(1, 0, rw, x);
    return 0;
}
