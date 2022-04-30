#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 100 + 5;
char set1[maxn], set2[maxn], res[maxn * 2];
int n;
int solve() {
    char tset[4][maxn] = {0};
    strcpy(tset[0], set1);
    strcpy(tset[1], set2);
    for(size_t i = 0; ;i++) {
        size_t offset = ((i + 1) % 2) * 2;
        int same = 0;
        for(size_t j = 0; j < n * 2; j++) {
            if(j < n) {
                tset[offset][j] = tset[(j + 1) % 2 + 2 - offset][j / 2];
                if(tset[offset][j] == res[j])   same++;
            }else{
                tset[offset + 1][j - n] = tset[(j + 1) % 2 + 2 - offset][j / 2];
                if(tset[offset + 1][j - n] == res[j])   same++;
            }
        }
        if(same == 2 * n)   return i + 1;
        if(!strcmp(tset[offset], set1) && !strcmp(tset[offset + 1], set2)) return -1;
    }
}
int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n >> set1 >> set2 >> res;
        cout << i + 1 << ' ' << solve() << endl;
    }
    return 0;
}