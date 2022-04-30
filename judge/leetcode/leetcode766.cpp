/*
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        for(int i = m - 1; i >= 0; i--) {
            for(int j = 1, k = i + 1; j < n && k < m; j++, k++) {
                if(matrix[i][0] != matrix[k][j])    return false;
            }
        }
        for(int i = 1; i < n; i++) {
            for(int j = i + 1, k = 1; j < n && k < m; j++, k++) {
                if(matrix[0][i] != matrix[k][j])    return false;
            }
        }
        return true;
    }
};
*/

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] != matrix[i - 1][j - 1]) {
                    return false;
                }
            }
        }
        return true;
    }
};
