#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1e5 + 5;
int n2 = 0, n4 = 0, n6 = 0, n8 = 0, mark[maxn], n, t;
bool solve() {
    if(n8 >= 1) return true;
    else if(n6 >= 1 && n2 >= 2) return true;
    else if(n4 >= 2 || (n4 >= 1 && n2 >= 3))    return true;
    else    return false;
}
int main() {
    //freopen("test.in", "r", stdin);
    char ch;
    memset(mark, 0, sizeof(mark));
    cin >> n;
    while(n--){
        cin >> t;
        mark[t]++;
        if(mark[t] == 2)    n2++;
        else if(mark[t] == 4)   n4++;
        else if(mark[t] == 6)   n6++;
        else if(mark[t] == 8)   n8++;
    }
    cin >> n;
    while(n--){
        cin >> ch >> t;
        if(ch == '+'){
            mark[t]++;
            if(mark[t] == 2)    n2++;
            else if(mark[t] == 4)   n4++;
            else if(mark[t] == 6)   n6++;
            else if(mark[t] == 8)   n8++;
        }else{
            if(mark[t] == 2)    n2--;
            else if(mark[t] == 4)   n4--;
            else if(mark[t] == 6)   n6--;
            else if(mark[t] == 8)   n8--;
            mark[t]--;
        }
        if(solve()){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}