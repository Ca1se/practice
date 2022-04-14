#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1e5 + 5;
int n, num = 0;
double maxp = -1;
double p, r;
vector<int> path[maxn];

void dfs(int pos, double price) {
    if(path[pos].size() == 0) {
        if(price > maxp) {
            maxp = price;
            num = 1;
        }else if(price == maxp) num++;
        return;
    }

    double tp = price * (1 + r);
    for(int i = 0; i < path[pos].size(); i++) {
        dfs(path[pos][i], tp);
    }
}

int main() {
    scanf("%d %lf %lf", &n, &p, &r);
    r = r / 100;
    int t, root;
    for(int i = 0; i < n; i++) {
        scanf("%d", &t);
        if(t == -1) {
            root = i;
            continue;
        }
        path[t].push_back(i);
    }
    dfs(root, p);
    printf("%.2f %d", maxp, num);
    return 0;
}
