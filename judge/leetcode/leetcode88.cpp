class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = 0, j = 0, k = 0;
        int T[m + n];
        vector<int>& more = m > n ? nums1 : nums2;
        vector<int>& less = m > n ? nums2 : nums1;
        if(m > n)   swap(m, n);
        while(i < m || j < n) {
            if(i >= m || (j < n && more[j] < less[i]))  T[k++] = more[j++];
            else {
                T[k++] = less[i++];
            }
        }
        for(i = 0; i < m + n; i++)  nums1[i] = T[i];
    }
};
