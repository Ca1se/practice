class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size() <= 2)  return 0;
        vector<int> leftMax(height.size(), 0), rightMax(height.size(), 0);
        int ans = 0;
        leftMax[0] = height[0];
        rightMax[height.size() - 1] = height.back();
        for(int i = 1; i < height.size(); i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }
        for(int i = height.size() - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }
        for(int i = 1; i < height.size() - 1; i++) {
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        return ans;
    }
};