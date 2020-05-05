#include<iostream>
#include<cmath>
#define ull unsigned long long
#define ll long long
using namespace std;
ll R, L, all;
const int maxn = 20;
int num[maxn], k;
ll search(ull element) {
    int ljudge = 1, rjudge = 1;
    ll i, j;
    for (i = L, j = R; i <= j;) {
        if (!(i % element))    ljudge = 0;
        if (!(j % element))    rjudge = 0;
        if (ljudge)  i++;
        if (rjudge)  j--;
        if (!(ljudge || rjudge))   break;
    }
    return (ljudge || rjudge) ? 0 : ((j - i) / element + 1);
}
void Case(int begin, int count, ull cele) {
    for (int i = begin; i < k; i++) {
        all += pow(-1, count) * search(cele * num[i]);
        Case(i + 1, count + 1, (ull)cele * num[i]);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin >> L >> R >> k;
    for (int i = 0; i < k; i++) {
        cin >> num[i];
    }
    Case(0, 0, 1);
    cout << R-L+1-all << endl;
}