#include <bits/stdc++.h>
using namespace std;
char arr[200];
char ans[200];
int main() {
    scanf("%s", arr);
    int diff = 'a' - 'A';
    if(arr[0] >= 'a' && arr[0] <= 'z') {
        bool j = true;
        ans[0] = arr[0] - diff;
        for(int i = 1; i < strlen(arr); i++) {
            if(arr[i] >= 'a' && arr[i] <= 'z') {
                j = false;
                break;
            }else {
                ans[i] = arr[i] + diff;
            }
            
        }
        if(j) {
            printf("%s\n", ans);
        }else {
            printf("%s\n", arr);
        }
    }else {
        bool j = true;
        ans[0] = arr[0] + diff;
        for(int i = 1; i < strlen(arr); i++) {
            if(arr[i] >= 'a' && arr[i] <= 'z') {
                j = false;
                break;
            }else {
                ans[i] = arr[i] + diff;
            }
        }
        if(j) {
            printf("%s\n", ans);
        }else {
            printf("%s\n", arr);
        }
    }
    return 0;
}
