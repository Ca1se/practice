#include<iostream>
#include<string>
using namespace std;
int main() {
    string a;
    int test, n;
    cin >> test;
    while(test--){
        cin >> n >> a;
        for(int i = 0; i < n * 2 - 1; i += 2){
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}