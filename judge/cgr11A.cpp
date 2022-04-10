#include<bits/stdc++.h>
using namespace std;
const int maxn = 50 + 5;
int num[maxn];
int main() {
    int test, n, sum;
    cin >> test;
    while(test--){
        sum = 0;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> num[i];
            sum += num[i];
        }
        sort(num, num + n);
        if(sum){
            cout << "YES" << endl;
            if(sum > 0){
                for(int i = n - 1; i >= 0; i--){
                    if(i != n - 1)  cout << ' ';
                    cout << num[i];
                }
            }else{
                for(int i = 0; i < n; i++){
                    if(i)   cout << ' ';
                    cout << num[i];
                }
            }
            cout << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}