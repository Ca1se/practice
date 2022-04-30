#include <cstdio>
using namespace std;

int main() {
    int t, n, pre, now, leftstart, leftend, rightstart, rightend, start, end;
    scanf("%d", &t);
    while(t--) {
        leftstart = leftend = rightstart = rightend = start = -1;
        scanf("%d%d", &n, &pre);
        for(int i = 1; i < n; i++) {
            scanf("%d", &now);
            if(start == -1 && now == pre) start = i - 1;
            else if(start != -1 && now != pre) {
                end = i - 1;
                if(leftstart == -1) {
                    leftstart = start;
                    leftend = end;
                }else {
                    rightstart = start;
                    rightend = end;
                }
                start = -1;
            }
            pre = now;
        }
        if(start != -1) {
            end = n - 1;
            if(leftstart == -1) {
                leftstart = start;
                leftend = end;
            }else {
                rightstart = start;
                rightend = end;
            }
        }
        int leftlen;
        if(rightstart == -1) {
            if(leftstart == -1) {
                puts("0");
            }else {
                leftlen = leftend - leftstart + 1;
                if(leftlen == 2) puts("0");
                else if(leftlen == 3) puts("1");
                else {
                    printf("%d\n", leftlen - 3);
                }
            }
        }else {
            printf("%d\n", rightend - leftstart + 1 - 3);
        }
    }
    return 0;
}
