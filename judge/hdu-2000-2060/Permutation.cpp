#include<iostream>
#include<cstdio>
using namespace std;
int main() {
    int test;
    scanf("%d", &test);
    for(int k = 0; k < test; k++){
        long long n, m;
        scanf("%lld%lld", &n, &m);
        if(m >= n / 2){
            cout << (n * (n - 1) / 2) << endl;
        }else{
            cout << ((4 * n - 4 * m - 2) * m / 2) << endl;
        }
    }
    return 0;
}/*注意输出范围*/