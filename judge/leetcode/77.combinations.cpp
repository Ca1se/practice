// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=77 lang=cpp
 * @lcpr version=
 *
 * [77] 组合
 */


// @lcpr-template-start
#include <bits/stdc++.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    vector<vector<int>> ans = {};

    void dfs(int now, int n, int k, vector<int>& qe)
    {
        for (int i = now; i <= n - k + 1; i++) {
            qe.push_back(i);
            if (k == 1) {
                ans.push_back(qe);
            } else {
                dfs(i + 1, n, k - 1, qe);
            }
            qe.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<int> tmp;
        dfs(1, n, k, tmp);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n2\n
// @lcpr case=end

// @lcpr case=start
// 1\n1\n
// @lcpr case=end

 */

