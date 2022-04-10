#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct String {
    ll hahaNum;
    string l3s, r3s;
    String(): hahaNum(), l3s(), r3s() {}
    String(ll num, string&& l3s, string&& r3s): hahaNum(num), l3s(l3s), r3s(r3s) {}
};
map<string, String> mp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t, n;
    string veriName, tmp, strVal, svName1, svName2;
    cin >> t;
    while(t--) {
        cin >> n;
        while(n--) {
            cin >> veriName >> tmp;
            String& veri = mp[veriName];
            ll cnt = 0;
            size_t pos = 0;
            if(tmp.size() == 1) {
                cin >> svName1 >> svName2 >> svName2; 
                String& sv1 = mp[svName1], & sv2 = mp[svName2];
                tmp = sv1.r3s + sv2.l3s;
                while((pos = tmp.find("haha", pos)) != string::npos) {
                    pos++, cnt++; 
                }
                veri.l3s = (sv1.l3s.size() == 3 ? sv1.l3s : (tmp.size() > 3 ? tmp.substr(0, 3) : tmp));
                veri.r3s = (sv2.r3s.size() == 3 ? sv2.r3s : (tmp.size() > 3 ? tmp.substr(tmp.size() - 3, 3) : tmp));
                veri.hahaNum = sv1.hahaNum + sv2.hahaNum + cnt;
            }else {
                cin >> strVal;
                while((pos = strVal.find("haha", pos)) != string::npos) {
                    pos++, cnt++; 
                }
                veri = String(cnt, 
                       (strVal.size() > 3 ? strVal.substr(0, 3) : strVal), 
                       (strVal.size() > 3 ? strVal.substr(strVal.size() - 3, 3) : strVal));
            }
        }
        cout << mp[veriName].hahaNum << endl;
    }
    return 0;
}
