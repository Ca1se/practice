#include<iostream>
#include<cmath>
#define ll long long
using namespace std;
const int maxn = 1e3;
ll num[maxn];
int main() {
    int n;
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    double sum = 0;
    ll max = -1;
    for (int i = 0; i < n; i++) {
        sum = sum * 2 + num[i];
        ll temp = (ll)(sum / pow(2, i + 1) + 0.9999999999);
        max = temp > max ? temp : max;
    }
    cout << max << endl;
}