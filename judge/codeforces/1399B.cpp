#include<iostream>
#include<algorithm>
using namespace std;
long long test, n, a[50 + 5], b[50 + 5];
long long solve() {
    long long ans = 0, mina = *min_element(a, a + n), minb = *min_element(b, b + n);
    for(int i = 0; i < n; i++){
        ans += max(a[i] - mina, b[i] - minb);
    }
    return ans;
}
int main() {
    //freopen("test.in", "r", stdin);
    cin >> test;
    for(int i = 0; i < test; i++){
        cin >> n;
        for(int j = 0; j < n; j++){
            cin >> a[j];
        }
        for(int j = 0; j < n; j++){
            cin >> b[j];
        }
        cout << solve() << endl;
    }
    return 0;
}