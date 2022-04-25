#include <cstdio>

int main() {
    int t, n, all, len;
    scanf("%d", &t);
    while(t--) {
        all = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &len);
            all += len - 1;
        }
        if(all & 1) {
            printf("errorgorn\n");
        }else {
            printf("maomao90\n");
        }
    }
    return 0;
}
