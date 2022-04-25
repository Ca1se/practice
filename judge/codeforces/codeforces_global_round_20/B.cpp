#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 2 * 1e5 + 5;
char str[maxn];

int main() {
    int t, len, need;
    scanf("%d", &t);
    while(t--) {
        need = 0;
        scanf("%s", str);
        len = strlen(str);
        if(len == 1) {
            printf("NO\n");
        }else if(str[len - 1] == 'A') {
            printf("NO\n");
        }else {
            for(int i = len - 1; i >= 0; i--) {
                if(str[i] == 'B') {
                    need++;
                }else {
                    need = max(0, need - 1);
                }
            }
            if(need) {
                printf("NO\n");
            }else {
                printf("YES\n");
            }
        }
    }
    return 0;
}
