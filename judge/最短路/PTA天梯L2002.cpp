#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, head, delHead = -1;
    int addr, val, next;
    map<int, pair<int, int>> list;
    int delListTail = -1;
    bool vis[(int) 1e4 + 5] = {0};
    scanf("%d%d", &head, &n);
    while(n--) {
        scanf("%d%d%d", &addr, &val, &next);
        list[addr] = make_pair(val, next);
    }
    int tar = head;
    vis[abs(list[head].first)] = true;
    while(tar != -1 && list[tar].second != -1) {
        auto& it = list[list[tar].second];
        if(vis[abs(it.first)]) {
            if(delListTail == -1) {
                delHead = delListTail = list[tar].second;
            }else {
                list[delListTail].second = list[tar].second;
                delListTail = list[tar].second;
            }
            list[tar].second = it.second;
            it.second = -1;
        }else {
            vis[abs(it.first)] = true;
            tar = list[tar].second;
        }
    }
    tar = head;
    while(tar != -1) {
        auto& it = list[tar];
        printf("%05d %d ", tar, it.first);
        printf(it.second == -1 ? "%d\n" : "%05d\n", it.second);
        tar = it.second;
    }
    tar = delHead;
    while(tar != -1) {
        auto& it = list[tar];
        printf("%05d %d ", tar, it.first);
        printf(it.second == -1 ? "%d\n" : "%05d\n", it.second);
        tar = it.second;
    }
    return 0;
}