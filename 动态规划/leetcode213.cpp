class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)  return nums[0];
        else if(n == 2) return max(nums[0], nums[1]);
        vector<int> dp(3);
        dp[2] = nums[0];
        dp[0] = nums[0];
        for(int i = 4; i < n + 1; i++) {
            dp[i % 3] = max(dp[(i - 2) % 3] + nums[i - 2], dp[(i - 1) % 3]);
        }
        int t = dp[n % 3];
        dp[1] = 0;
        dp[2] = 0;
        for(int i = 3; i < n + 2; i++) {
            dp[i % 3] = max(dp[(i - 2) % 3] + nums[i - 2], dp[(i - 1) % 3]);
        }
        return max(t, dp[(n + 1) % 3]);
    }
};