// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=179 lang=cpp
 * @lcpr version=
 *
 * [179] 最大数
 */


// @lcpr-template-start
#include <bits/stdc++.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution
{
public:
    int len(int num)
    {
        int base = 10;
        int len = 1;
        for (; len <= 10; len++) {
            if (num / base == 0)
                break;
            base *= 10;
        }
        return len;
    }

    string largestNumber(vector<int>& nums)
    {
        sort(nums.begin(), nums.end(), [&](int a, int b){
            if (a == b)
                return false;

            int len_a = len(a);
            int len_b = len(b);
            bool flag = false;
            if (len_a < len_b) {
                swap(a, b);
                swap(len_a, len_b);
                flag = true;
            } // make sure len(a) >= len(b)
            int base_a = int(pow(10, len_a - 1));
            int base_b = int(pow(10, len_b - 1));
            int tmp_b = b;
            for (int k = 0; k < len_a / len_b; k++) {
                for (int i = 0; i < len_b; i++) {
                    int aa = a / base_a;
                    int bb = tmp_b / base_b;
                    if (aa != bb)
                        return bool((aa > bb) xor flag);
                    a -= aa * base_a;
                    tmp_b -= bb * base_b;
                    base_a /= 10;
                    base_b /= 10;
                }
                base_b = int(pow(10, len_b - 1));
                tmp_b = b;
            }
            if (base_a > 0) {
                int len_ra4 = len(base_a);
                a = a * base_b * 10 + tmp_b;
                a /= int(pow(10, len_ra4));
                base_a = base_b;
                for (int i = 0; i < len_b; i++) {
                    int aa = a / base_a;
                    int bb = tmp_b / base_b;
                    if (aa != bb)
                        return bool((aa > bb) xor flag);
                    a -= aa * base_a;
                    tmp_b -= bb * base_b;
                    base_a /= 10;
                    base_b /= 10;
                }
                return true;
            } else {
                return bool((len_a < len_b) xor flag);
            }
        });
        string ans;
        if (nums[0] == 0) {
            return "0";
        } else {
            for (int num: nums) {
                ans += to_string(num);
            }
            return ans;
        }
    }
};
// @lc code=end

/*
// @lcpr case=start
// [10,2]\n
// @lcpr case=end

// @lcpr case=start
// [3,30,34,5,9]\n
// @lcpr case=end

 */

