#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
const int maxn = 25 + 5;

vector<string> rem;
int d[maxn][maxn];
int mark[maxn];
int n, m, cnt = 1;

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = d[i][j] || (d[i][k] && d[k][j]);
            }
        }
    }
}

void pic(int s, int c) {
    if (c)   cout << ", ";
    cout << rem[s];
    mark[s] = 1;
    for (int i = s + 1; i < n; i++) {
        if (d[s][i] && d[i][s] && !mark[i]) {
            pic(i, c + 1);
        }
    }
}

int main() {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    while (cin >> n >> m && n && m) {
        if(cnt != 1)    cout << endl;
        string name[2];
        rem.clear();
        memset(d, 0, sizeof(d));
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < m && cin >> name[0] >> name[1]; i++) {
            int t[2];
            for (int j = 0; j < 2; j++) {
                vector<string>::iterator tmp = find(rem.begin(), rem.end(), name[j]);
                if (tmp == rem.end()) {
                    rem.push_back(name[j]);
                    t[j] = rem.size() - 1;
                }
                else {
                    t[j] = tmp - rem.begin();
                }
            }
            d[t[0]][t[1]] = 1;
        }
        floyd();
        cout << "Calling circles for data set " << cnt++ << ":" << endl;
        for (int i = 0; i < n; i++) {
            if (!mark[i]) {
                pic(i, 0);
                cout << endl;
            }
        }
    }
}
