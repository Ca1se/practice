#include<iostream>
#include<set>
#include<map>
#include<cstring>
using namespace std;
set<int> sides;
map<int, int> sidecount;
int setbox[12], box[6], mark[3];
int main() {
    ios::sync_with_stdio(false);
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    memset(mark, 0, sizeof(mark));
    for (int i = 0; cin >> setbox[i++] >> setbox[i]; i++) {
        sides.insert(setbox[i - 1]);
        sides.insert(setbox[i]);
        if (sidecount.find(setbox[i - 1]) != sidecount.end())  sidecount[setbox[i - 1]] += 1;
        else    sidecount[setbox[i - 1]] = 1;
        if (sidecount.find(setbox[i]) != sidecount.end())  sidecount[setbox[i]] += 1;
        else    sidecount[setbox[i]] = 1;
        if (!((i + 1) % 12)) {
            auto it = sides.begin();
            if (sides.size() > 3) {
                cout << "IMPOSSIBLE\n";
                continue;
            }else if (sides.size() == 3) {
                for (int j = 0; j < 6; j++) {
                    if (it == sides.end()) it = sides.begin();
                    box[j] = *(it++);
                }
            }else if (sides.size() == 2) {
                auto it1 = sidecount.begin();
                box[0] = box[2] = *it;
                box[1] = box[3] = *((++it)--);
                if (it1->second > (++it1)->second)   box[4] = box[5] = *it;
                else   box[4] = box[5] = *(++it);
            }else {//1
                for (int j = 0; j < 6; j++) {
                    box[j] = *it;
                }
            }
            for (int j = 0; j < 12; j += 2) {
                for (int k = 0; k < 6; k += 2) {
                    if (setbox[j] + setbox[j + 1] == box[k] + box[k + 1] && setbox[j] * setbox[j + 1] == box[k] * box[k + 1] && mark[k / 2] < 2) {
                        mark[k / 2]++;
                        break;
                    }
                }
            }
            if (mark[0] * mark[1] * mark[2] == 8)  cout << "POSSIBLE\n";
            else    cout << "IMPOSSIBLE\n";
            memset(mark, 0, sizeof(mark));
            sides.clear();
            sidecount.clear();
            i = -1;
        }
    }
    return 0;
}