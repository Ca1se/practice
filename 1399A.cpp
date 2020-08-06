#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int test, n, a[50 + 5];
bool solve() {
    int cnt = 0;
    sort(a, a + n);
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(abs(a[i] - a[j]) <= 1){
                cnt++;
                break;
            }
        }
    }
    return cnt == n - 1 ? true : false;
}
int main() {
    //freopen("test.in", "r", stdin);
    cin >> test;
    for(int i = 0; i < test; i++){
        cin >> n;
        for(int j = 0; j < n; j++){
            cin >> a[j];
        }
        if(solve()){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}