class Solution {
public:
    string removeDuplicates(string S) {
        string ans;
        for(auto it: S) {
            if(ans.size() && ans.back() == it) {
                ans.pop_back();
            }else {
                ans.push_back(it);
            }
        }
        return ans;
    }
};
