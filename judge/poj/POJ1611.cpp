#include <cstdio>
#include <cstring>


static const int maxn = 30000 + 5;
int n, m;
int arr[maxn];
int num[maxn];

int find(int t)
{
    return (arr[t] == -1 ? t : arr[t] = ::find(arr[t]));
}

void Union(int x, int y)
{
    int xx = ::find(x), yy = ::find(y);
    if(xx == yy && xx != -1)
        return;

    if(xx == x && yy != y) {
        arr[xx] = yy;
        num[yy] += num[xx];
    }else if(xx != x && yy == y) {
        arr[yy] = xx;
        num[xx] += num[yy];
    }else if(xx == x && yy == y) {
        arr[xx] = yy;
        num[yy] += num[xx];
    }else {
        arr[xx] = yy;
        num[yy] += num[xx];
    }
}



int main() {
    int k, a, b;
    while(scanf("%d%d", &n, &m) && (n != 0 || m != 0)) {
        for(int i = 0; i < n; i++) {
            arr[i] = -1;
            num[i] = 1;
        }
        for(int i = 0; i < m; i++) {
            scanf("%d", &k);
            scanf("%d", &a);
            for(int j = 0; j < k - 1; j++) {
                scanf("%d", &b);
                Union(a, b);
            }
        }
        printf("%d\n", num[::find(0)]);
    }
    return 0;
}
