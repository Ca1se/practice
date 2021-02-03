//对并查集的简单运用, 不知道为什么标为困难...
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        memset(mp, -1, sizeof(mp));
        memset(deep, 0, sizeof(deep));

        for(size_t i = 0; i < strs.size(); i++) {
            for(size_t j = i + 1; j < strs.size(); j++) {
                int r1 = Find(i), r2 = Find(j);
                if(r1 == r2)  continue;
                if(involve(strs[i], strs[j]))   Union(r1, r2);
            }
        }

        int ans = 0;
        for(size_t i = 0; i < strs.size(); i++) {
            if(mp[i] < 0)  ans++;
        }
        return ans;
    }
private:
    static const int maxn = 300;
    int mp[maxn];
    int deep[maxn];

    bool involve(const string& s1, const string& s2) {
        int t = 0;
        for(size_t i = 0; i < s1.length(); i++) {
            if(s1[i] - s2[i])   t++;
            if(t > 2)   return false;
        }
        return (t == 2) || !t;
    }

    int Find(int pos) {
        return (mp[pos] < 0 ? pos : mp[pos] = Find(mp[pos]));
    }

    void Union(int p1, int p2) {
        int r1 = Find(p1), r2 = Find(p2);
        if(deep[r1] <= deep[r2])   mp[r1] = r2;
        else    mp[r2] = r1;
        if(deep[r1] == deep[r2])    deep[r2]++;
    }
};