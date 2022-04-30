class Solution {//O(nlogn)
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return false;

        int left_min = nums[0];
        multiset<int> s;
        for(int i = 2; i < n; i++) {
            s.insert(nums[i]);
        }

        for(int i = 1; i < n - 1; i++) {
            if(left_min < nums[i]) {
                auto it = s.upper_bound(left_min);
                if(it != s.end() && *it < nums[i]) {
                    return true;
                }
            }
            left_min = min(left_min, nums[i]);
            s.erase(s.find(nums[i + 1]));
        }
        return false;
    }
    
};
class Solution {//O(n)
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if(n < 3)   return false;
        int maxk = -1e9 - 1;
        stack<int> s;
        s.push(nums[n - 1]);
        for(int i = n - 2; i >= 0; i--) {
            if(nums[i] < maxk) {
                return true;
            }
            while(!s.empty() && nums[i] > s.top()) {
                maxk = s.top();
                s.pop();
            }
            if(nums[i] > maxk) {
                s.push(nums[i]);
            }
        }
        return false;
    }
};