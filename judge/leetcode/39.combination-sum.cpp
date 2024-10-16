/*
 * @lc app=leetcode.cn id=39 lang=cpp
 * @lcpr version=
 *
 * [39] 组合总和
 */


// @lcpr-template-start
#include <bits/stdc++.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    vector<vector<int>> ans = {};
    vector<int> qe = {};
    int target = 0;

    void dfs(const vector<int>& candi, int pos, int pre_sum)
    {
        for (int i = pos; i < candi.size(); i++) {
            int candi_num = candi[i];
            if (pre_sum + candi_num == target) {
                qe.push_back(candi_num);
                ans.push_back(qe);
                qe.pop_back();
                break;
            } else if (pre_sum + candi_num < target) {
                qe.push_back(candi_num);
                dfs(candi, i, pre_sum + candi_num);
                qe.pop_back();
            } else {
                break;
            }
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        this->target = target;
        sort(candidates.begin(), candidates.end(), [](int a, int b) {
            return a < b;
        });
        dfs(candidates, 0, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,6,7]\n7\n
// @lcpr case=end

// @lcpr case=start
// [2,3,5]\n8\n
// @lcpr case=end

// @lcpr case=start
// [2]\n1\n
// @lcpr case=end

 */

