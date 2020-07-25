#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 7;

int w[maxn][maxn];
int mark[maxn];
int dis[maxn];
int path[maxn];
void init() {
    memset(w, 0x3f, sizeof(w));
    memset(mark, 0, sizeof(mark));
    memset(dis, 0x3f, sizeof(dis));
    w[0][1] = w[1][0] = 6;
    w[0][4] = w[4][0] = 8;
    w[1][2] = w[2][1] = 15;
    w[3][2] = w[2][3] = 20;
    w[2][5] = w[5][2] = 8;
    w[6][3] = w[3][6] = 13;
    w[4][5] = w[5][4] = 2;
    w[5][6] = w[6][5] = 7;
}
//适用于无负权边的有向无向图
void dijkstra(int s) {
    dis[s] = 0;
    for(int i = 0; i < maxn; i++){
        int x, m = INF;
        for(int j = 0; j < maxn; j++)   if(!mark[j] && dis[i] <= m) m = dis[x = j];
        mark[x] = 1;
        for(int j = 0; j < maxn; j++)   dis[j] = min(dis[j], dis[x] + w[x][j]);
    }
}
//未优化,适用于无负权边的有向无向图和含负权边的有向图
bool bellman_ford(int s) {
    for(int i = 0; i < maxn; i++){
        dis[i] = w[s][i];
    }
    dis[s] = 0;
    for(int i = 0; i < maxn - 1; i++){
        for(int j = 0; j < maxn; j++){
            for(int k = 0; k < maxn; k++){
                dis[k] = min(dis[k], dis[j] + w[j][k]);
            }
        }
    }
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j < maxn; j++){
            if(dis[j] > dis[i] + w[i][j]){
                return false;
            }
        }
    }
    return true;
}

//用于计算两两点间的最短距离
void floyd() {
    for(int i = 0; i < maxn; i++){
        w[i][i] = 0;
    }
    for(int k = 0; k < maxn; k++){
        for(int i = 0; i < maxn; i++){
            for(int j = 0; j < maxn; j++){
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
            }
        }
    }
}
