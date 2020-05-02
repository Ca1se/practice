#include<iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i=0;i<t;i++){
        double n;
        cin >> n;
        cout << (long long)(6*n*n) << endl;
    }
    return 0;
}