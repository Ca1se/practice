class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(3);
        dp[0] = 0;
        dp[1] = 0;
        for(int i = 2; i < n + 2; i++) {
            dp[i % 3] = max(dp[(i - 2) % 3] + nums[i - 2], dp[(i - 1) % 3]);
        }
        return dp[(n + 1) % 3];
    }
};