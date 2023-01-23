/*
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 8;
char mp[maxn][maxn];
int xmark[maxn], mpsize, cnum;

int solve(int y, int step) {
    if(step == cnum)    return 1;
    int sum = 0;
    for(int i = y + 1; i < mpsize; i++){
        for(int j = 0; j < mpsize; j++){
            if(!xmark[j] && mp[i][j] == '#'){
                xmark[j] = 1;
                sum += solve(i, step + 1);
                xmark[j] = 0;
            }
        }
    }
    return sum;
}
int main() {
    while(cin >> mpsize >> cnum && (mpsize != -1 || cnum != -1)){
        for(int i = 0; i < mpsize; i++){
            for(int j = 0; j < mpsize; j++){
                cin >> mp[i][j];
            }
        }
        cout << solve(-1, 0) << endl;
    }
}
*/



#include <cstdio>

static const int maxn = 10;
int n, k, ans, xmark[maxn];
char arr[maxn][maxn];

int solve(int row, int step) {
    if(step == k) return 1;
    int sum = 0;
    for(int i = row; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(arr[i][j] == '#' && !xmark[j]) {
                xmark[j] = true;
                sum += solve(i + 1, step + 1);
                xmark[j] = false;
            }
        }
    }
    return sum;
}

int main() {
    while(true) {
        scanf("%d%d", &n, &k);
        if(n == -1 && k == -1)
            break;
        for(int i = 0; i < n; i++)
            scanf("%s", arr[i]);
        printf("%d\n", solve(0, 0));
    }
    return 0;
}
