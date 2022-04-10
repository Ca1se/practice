#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestSubstring(string s, int k) {
        return dfs(s, 0, s.size(), k);
    }
private:
    int dfs(const string& s, int l, int r, int k) {
        vector<int> cnt(26, 0);
        for(int i = l; i < r; i++) {
            cnt[s[i] - 'a']++;
        }
        char split = 0;
        for(int i = 0; i < 26; i++) {
            if(cnt[i] && cnt[i] < k) {
                split = i + 'a';
                break;
            }
        }
        if(!split)  return r - l;
        int i = l;
        int maxx = 0;
        while(i < r) {
            while(i < r && s[i] == split) {
                i++;
            }
            if(i == r)  break;
            int j = i;
            while(j < r && s[j] != split) {
                j++;
            }
            maxx = max(maxx, dfs(s, i, j, k));
            i = j;
        }
        return maxx;
    }
};