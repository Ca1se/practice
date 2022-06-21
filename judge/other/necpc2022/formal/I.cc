#include <cstdio>
#include <cmath>
#include <math.h>
int main() {
    double ans = 0;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            for(int k = 0; k < 100; k++) {
                ans += 1.0 / 4 * pow(1.0 / 4, i) * pow(1.0 / 3, j) * pow(1.0 / 2, k) * (i + j + k + 1);
            }
        }
    }
    printf("%lf\n", ans);
    return 0;
}
