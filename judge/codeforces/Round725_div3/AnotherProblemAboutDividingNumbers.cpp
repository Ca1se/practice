#include <bits/stdc++.h>
using namespace std;
int fac(int n) {
    int res = 0;
    for(int i = 2; i * i <= n; i++) {
        while(n % i == 0) {
            res++;
            n /= i;
        }
    }
    if(n > 1) {
        res++;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t, a, b, k;
    cin >> t;
    while(t--) {
        cin >> a >> b >> k;
        if(a != 1 || b != 1) {
            if(k == 1) {
                if((a % b == 0 || b % a == 0) && a != b) {
                    cout << "YES" << endl;
                }else {
                    cout << "NO" << endl;
                }
            }else if(k == 2 && a != 1 && b != 1) {
                cout << "YES" << endl;
            }else {
                int sum = 0;
                if(k <= fac(a) + fac(b)) {
                    cout << "YES" << endl;
                }else {
                    cout << "NO" << endl;
                }
            }
        }else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

