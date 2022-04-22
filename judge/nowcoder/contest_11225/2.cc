#include <cstdio>
#include <cmath>
using namespace std;
using ll = long long;
int main() {
    int t;
    ll n, a, b;
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        scanf("%lld%lld%lld", &n, &a, &b);
        double mh = sqrt(double(2 * n + 0.25)) - 0.5;
        ll h = mh;
        if(a > b) {
            printf("niuniu\n");
        }else if(a < b) {
            printf("niumei\n");
        }else {
            if(h % 2) {
                printf("niumei\n");
            }else {
                printf("niuniu\n");
            }
        }
    }
    return 0;
}
