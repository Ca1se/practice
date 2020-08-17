#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, t;
ll arr[30][30], g;
void make_arr() {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i & 1){
                arr[i][j] = (ll)1 << (i + j);
            }else{
                arr[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout << arr[i][0];
        for(int j = 1; j < n; j++){
            cout << " " << arr[i][j];
        }
        cout << endl;
        cout.flush();
    }
}
ostream& operator<< (ostream& out, pair<int, int>& x){
    out << x.first << " " << x.second << endl;
    out.flush();
    return out;
}
int main() {
    cin >> n;
    make_arr();
    cin >> t;
    while(t--){
        pair<int, int> point(1, 1);
        cin >> g;
        cout << point;
        for(int i = 1; i <= (n - 1) * 2; i++){
            if(point.first & 1){//单数层
                if(g & ((ll)1 << i))    point.first++;
                else    point.second++;
            }else{
                if(g & ((ll)1 << i))    point.second++;
                else    point.first++;
            }
            cout << point;
        }
    }
    return 0;
}