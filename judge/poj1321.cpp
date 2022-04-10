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