#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <string>
#include <map>
using namespace std;

char skymap[105][105];
int mark[105][105];
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int m, n;
map<string, char> link;

float provalue(vector<pair<int, int> >& points){
    double y = 0, x = 0, res = 0;
    for(int i = 0; i < points.size(); i++){
        y += points[i].first;
        x += points[i].second;
    }
    y = y / points.size();
    x = x / points.size();
    for(int i = 0; i < points.size(); i++){
        res += (y - points[i].first) * (y - points[i].first) * (y - points[i].first) * (y - points[i].first);
        res += (x - points[i].second) * (x - points[i].second) * (x - points[i].second) * (x - points[i].second);
    }
    return res;
}

void bfs(int y, int x){
    queue<pair<int, int> > q;
    vector<pair<int, int> > points;
    q.push(make_pair(y, x));
    points.push_back(make_pair(y, x));
    mark[y][x] = 1;
    while (!q.empty()){
        pair<int, int> tmp = q.front();
        q.pop();
        for (int i = 0; i < 8; i++){
            int ny = tmp.first + dy[i], nx = tmp.second + dx[i];
            if (ny < 0 || ny >= m || nx < 0 || nx >= n){
                continue;
            }
            else if (mark[ny][nx] == 0 && skymap[ny][nx] == '1'){
                mark[ny][nx] = 1;
                q.push(make_pair(ny, nx));
                points.push_back(make_pair(ny, nx));
            }
        }
    }
    char s[100];
    sprintf(s, "%f", provalue(points) + points.size());
    char a;
    if (link[s] != '\0'){
        a = link[s];
    }
    else{
        a = link[s] = 'a' + link.size() - 1;
    }
    for (vector<pair<int, int> >::iterator it = points.begin(); it != points.end(); it++){
        skymap[(*it).first][(*it).second] = a;
    }
}
int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    scanf("%d%d", &n, &m);
    memset(skymap, 0, sizeof(skymap));
    memset(mark, 0, sizeof(mark));
    link.clear();
    for (int i = 0; i < m; i++){
        scanf("%s", skymap[i]);
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (skymap[i][j] == '1' && mark[i][j] == 0){
                bfs(i, j);
            }
        }
    }
    for (int i = 0; i < m; i++){
        printf("%s\n", skymap[i]);
    }
}