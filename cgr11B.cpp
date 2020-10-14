#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;

int main() {
    char wal[maxn];
    int test, m, n, sw, ans, blank, begin;
    vector<int> l;
    cin >> test;
    while(test--){
        l.clear();
        sw = 0, ans = 0, blank = 0, begin = 0;
        memset(wal, 0, sizeof(wal));
        cin >> m >> n;
        for(int i = 1; i <= m; i++){
            cin >> wal[i];
            if(sw == 0 && wal[i] == 'L'){
                sw = 1;
                begin = i;
            }else if(sw == 1 && wal[i] == 'W'){
                ans++;
                sw = 0;
                if(begin == 1){
                    blank = i - begin;
                    continue;
                }
                l.push_back(i - begin);
            }else if(wal[i] == 'W'){
                ans++;
                if(wal[i - 1] == 'W')   ans++;
            }
        }
        if(sw){
            blank += m - begin + 1;
        }
        sort(l.begin(),l.end(),[](int l, int r){
            return l < r;
        });
        for(int i = 0; i < l.size(); i++){
            if(l[i] >= n){
                ans += n * 2;
                if(l[i] == n)   ans++;
                n = 0;
                break;
            }
            ans += l[i] * 2 + 1;
            n -= l[i];
        }
        if(!ans)    ans--;
        ans += min(n, blank) * 2;
        cout << max(0, ans) << endl;
    }    
    return 0;
}