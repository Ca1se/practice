class NumArray {
public:
    NumArray(vector<int>& nums) {
        dist.resize(nums.size());
        long long sum = 0;
        for(int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            dist[i] = sum;
        }
    }
    
    int sumRange(int i, int j) {
        return dist[j] - (i ? dist[i - 1] : 0);
    }
private:
    vector<int> dist;
};
