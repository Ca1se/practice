#include<iostream>
#define ll long long
using namespace std;
ll n;
int main() {
    //freopen("test.in", "r", stdin);
    int test;
    cin >> test;
    for(int i = 0; i < test; i++){
        cin >> n;
        cout << (n / 2 + 1) << endl;
    }
}