/*
 * @lc app=leetcode.cn id=17 lang=cpp
 * @lcpr version=
 *
 * [17] 电话号码的字母组合
 */


// @lcpr-template-start
#include <bits/stdc++.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    string dict[10] = {
        "",
        "",
        "abc",
        "def", 
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"
    };

    vector<string> ans = {};

    void dfs(const string& digits, string& str, int pos)
    {
        string a = dict[digits[pos] - '0'];
        for (char c: a) {
            str.push_back(c);
            if (pos + 1 == digits.length()) {
                ans.push_back(str);
            } else {
                dfs(digits, str, pos + 1);
            }
            str.pop_back();
        }
    }

    vector<string> letterCombinations(string digits)
    {
        if (digits.length() == 0)
            return vector<string>{};

        string tmp = "";
        dfs(digits, tmp, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "23"\n
// @lcpr case=end

// @lcpr case=start
// ""\n
// @lcpr case=end

// @lcpr case=start
// "2"\n
// @lcpr case=end

 */

