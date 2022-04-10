#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn = 1000;
char s[maxn];
int solve() {
    int len = strlen(s);
    vector<int> t;
    int r = 0, ans = 0;
    for(int i = 0; i < len; i++){
        if(s[i] == '0'){
            t.push_back(r);
            r = 0;
        }else{
            r++;
        }
    }
    t.push_back(r);
    sort(t.begin(), t.end(),[](int x, int y){
        return x > y;
    });
    for(int i = 0; i < t.size(); i++){
        if(!(i & 1))  ans += t[i];  
    }
    return ans;
}
int main() {
    //freopen("test.in", "r", stdin);
    ios::sync_with_stdio(false);
    int test;
    cin >> test;
    while(test--){
        cin >> s;
        cout << solve() << endl;
    }
}