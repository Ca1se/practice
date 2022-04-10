#include<bits/stdc++.h>
using namespace std;
struct stu {
    string name;int id;
}stus[3 * 5 * (int)1e4];
int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i = 0; i < 3 * n; i += 3){
            cin >> stus[i].name >> stus[i].id >> stus[i + 1].name >> stus[i + 1].id >> stus[i + 2].name >> stus[i + 2].id;
        }
        sort(stus, stus + 3 * n, [](const stu& lhs, const stu& rhs){
            return lhs.id < rhs.id;
        });
        for(int i = 0; i < 3 * n; i += 3){
            cout << "ACM-" << i / 3;
            cout << " " << stus[i + 2].name << " " << stus[i + 1].name << " " <<stus[i].name << endl;
        }
    }
}