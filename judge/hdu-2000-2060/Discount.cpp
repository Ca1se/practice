#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 100 + 5;
int main() {
    int test, b[maxn];
    double c[maxn];
    cin >> test;
    for(int i = 0; i < test; i++){
        int n;
        double ans = -1;
        cin >> n;
        for(int j = 0; j < n; j++){
            cin >> b[j] >> c[j];
        }
        for(int j = 0; j < n; j++){
            ans = max(ans, (1.0 - c[j]) / ((double)b[j] - c[j] + 1));
        }
        printf("%.5f\n", ans);
    }
    return 0;
}