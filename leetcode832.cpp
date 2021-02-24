class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m / 2; j++) {
                if(A[i][j] == A[i][m - j - 1])    A[i][j] = A[i][m - j - 1] = !A[i][j];
            }
            if(m % 2)   A[i][m / 2] = !A[i][m / 2];
        }
        return A;
    }
};
