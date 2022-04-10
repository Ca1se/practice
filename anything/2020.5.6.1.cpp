#include<iostream>
#include<vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int N;
   // freopen("test.in", "r", stdin);
    while (cin >> N && N)
    {
        vector<vector<int>> a;
        for (int i = 0; i < N; i++) {
            vector<int> t;
            int temp[2];
            cin >> temp[0] >> temp[1];
            t.push_back(temp[0]);
            t.push_back(temp[1]);
            a.push_back(t);
            auto it = a.begin();
            int siz = a.size();
            for (int i = 0; i < siz-1; i++) {
                if (temp[0] >= (*it)[0] && temp[1] >= (*it)[1]) {
                    it=a.erase(it);
                    continue;
                }else if(temp[0] > (*it)[0] || temp[1] > (*it)[1]){
                    it++;
                    continue;
                }
                a.pop_back();
                break;
            }
        }
        cout << a.size() << "\n";
    }
    return 0;
}
