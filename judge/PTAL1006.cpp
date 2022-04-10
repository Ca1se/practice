#include<bits/stdc++.h>
using namespace std;
int main() {
    using ll = long long;
    ll n;
    cin >> n;
    int begin = 0, end = 0;
    for(int i = 2; i <= (int) sqrt(n) + 1; i++) {
        if(n % i == 0) {
            if(begin == 0)  begin = end = i;
            int res = i, e = i;
            while(n % (res * (e + 1)) == 0) {
                e++;
                res *= e;
            }
            if(end - begin < e - i) {
                end = e;
                begin = i;
            } 
        }
    }
    if(begin == 0) {
        cout << 1 << endl << n;
    }else {
        cout << end - begin + 1 << endl;
        cout << begin;
        for(int i = begin + 1; i <= end; i++) {
            cout << "*" << i;
        }
    }
    cout << endl;
    return 0;
}
