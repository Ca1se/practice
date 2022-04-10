#include <bits/stdc++.h>
using namespace std;
const int maxl = 1e5 + 5;
char arr[maxl];
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", arr);
        int cnt = 0, flag = 0;
        for(int i = 0; i < strlen(arr) && cnt < 2; i++) {
            if(arr[i] == '1') {
                flag = 0;
                continue;
            }else {
                if(flag) continue;
                else {
                    flag = 1;
                    cnt++;
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
