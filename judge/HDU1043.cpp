#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
using namespace std;
const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
const int maxn = 362880 + 5;
bool vis[maxn];
string path[maxn];
struct Step {
    char mp[9];
    string step;
    int x;
    Step(char* m, int pos): x(pos) {
        strcpy(mp, m);
    }
};

int cantor(char* arr) {
    int res = 0;
    for(int i = 0; i < 9; i++) {
        int small = 0;
        for(int j = i + 1; j < 9; j++) {
            if(arr[i] > arr[j]) small++;
        }
        res += small * FAC[8 - i];
    }
    return res;
}

void solve() {
    memset(vis, 0, sizeof(vis));
    queue<Step> q;
    char arr[] = "12345678x";
    q.push(Step(arr, 8));

    while(!q.empty()) {
        Step t = q.front(); q.pop();
        int can = cantor(t.mp);
        if(vis[can])    continue;
        vis[can] = true;
        path[can] = t.step;
        if(t.x > 2 && (t.step.size() == 0 || t.step.front() != 'u')) {
            q.push(t);
            auto& it = q.back();
            swap(it.mp[it.x], it.mp[it.x - 3]);
            it.step.insert(it.step.begin(), 'd');
            it.x -= 3;
        }

        if(((t.x + 1) % 3) && (t.step.size() == 0 || t.step.front() != 'r')) {
            q.push(t);
            auto& it = q.back();
            swap(it.mp[it.x], it.mp[it.x + 1]);
            it.step.insert(it.step.begin(), 'l');
            it.x += 1;
        }

        if(t.x < 6 && (t.step.size() == 0 || t.step.front() != 'd')) {
            q.push(t);
            auto& it = q.back();
            swap(it.mp[it.x], it.mp[it.x + 3]);
            it.step.insert(it.step.begin(), 'u');
            it.x += 3;
        }

        if((t.x % 3) && (t.step.size() == 0 || t.step.front() != 'l')) {
            q.push(t);
            auto& it = q.back();
            swap(it.mp[it.x], it.mp[it.x - 1]);
            it.step.insert(it.step.begin(), 'r');
            it.x -= 1;
        }
    }
}

int main() {
    char mp[10] = {0};
    solve();
    while(scanf(" %c", mp) == 1) {
        for(int i = 1; i < 9; i++) {
            scanf(" %c", mp + i);
        }
        int hash = cantor(mp);
        if(vis[hash]) {
            printf("%s\n", path[hash].c_str());
        }else {
            printf("unsolvable\n");
        }
    }
    return 0;
}