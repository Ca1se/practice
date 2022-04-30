class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n == 0)  return false;
        else if(n == 1) return nums.front() == target;
        int i = 0, j = n - 1;
        while(i <= j) {
            int m = (i + j) / 2;
            if(nums[m] == target)   return true;
            else if(nums[m] == nums[i] && nums[m] == nums[j])   i++,j--;
            else if(nums[m] >= nums[i]){
                if(nums[m] > target && target >= nums[i]) j = m - 1;
                else    i = m + 1;
            }else {
                if(target > nums[m] && nums[j] >= target) i = m + 1;
                else    j = m - 1;
            }
        }
        return false;
    }
};