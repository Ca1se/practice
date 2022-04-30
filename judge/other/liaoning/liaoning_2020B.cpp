#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, q, u, v;
    scanf("%d%d", &n, & q);
    while(q--){
        scanf("%d%d", &u, &v);
        if(u == v){
            printf("0\n");
        }else if(__gcd(u, v) == 1){
            printf("1\n");
        }else{
            printf("2\n");
        }
    }
    return 0;
}