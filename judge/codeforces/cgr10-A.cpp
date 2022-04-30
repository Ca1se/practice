#include<iostream>
#include<map>
using namespace std;
int main() {
    map<int, int> mp;
    int test;
    cin >> test;
    while(test--){
        mp.clear();
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            int t;
            cin >> t;
            mp[t]++;
        }
        if(mp.size() == 1)  cout << n << endl;
        else    cout << 1 << endl;
    }
}