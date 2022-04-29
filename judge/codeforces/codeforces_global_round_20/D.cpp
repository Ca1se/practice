#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2 * 1e5 + 5;
int arr1[maxn];
int arr2[maxn];
int owe[maxn];

int main() {
    int t, n, pre, pos;
    bool jud;
    scanf("%d", &t);
    while(t--) {
        memset(owe, 0, sizeof owe);
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", arr1 + i);
        }
        for(int i = 0; i < n; i++) {
            scanf("%d", arr2 + i);
        }
        if(arr1[n - 1] != arr2[n - 1]) {
            puts("NO");
            continue;
        }
        pre = arr1[n - 1];
        pos = n - 2;
        jud = true;
        for(int i = n - 2; i >= 0;) {
            if(arr1[pos] != arr2[i]) {
                if(pre == arr2[i]) {
                    owe[pre]++;
                }else if(owe[arr1[pos]]) {
                    owe[arr1[pos]]--;
                    pos--;
                    continue;
                }else {
                    jud = false;
                    break;
                }
                i--;
                continue;
            }
            pre = arr1[pos];
            pos--, i--;
        }
        if(jud) {
            puts("YES");
        }else {
            puts("NO");
        }
    }
    return 0;
}
