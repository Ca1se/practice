class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        bool j = A.front() >= A.back();
        for(int i = 1; i < A.size(); i++) {
            if(A[i - 1] != A[i] && (A[i - 1] > A[i]) ^ j)  return false;
        }
        return true;
    }
};
