#include<bits/stdc++.h>
using namespace std;
int main() {
    int test, n, m;
    int a = 0, b = 0, r;
    cin >> test;
    while(test--){
        a = b = 0;
        cin >> n >> m;
        if (n == 1 || n == 2){
            cout << 0 << endl;
            continue;
        }
        for(int i = 2; i < n; i++){
            r = (a + b + 1) % m;
            a = b, b = r;
        }
        cout << r << endl;
    }
    return 0;
}