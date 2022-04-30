class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> q(matrix.size() * matrix[0].size());
        int mn[2] = {int(matrix[0].size() - 1), int(matrix.size() - 1)};
        bool j = false;
        int pos = 0, pre = 0, choose = 0, x = 0, y = 0;
        while(pos < q.size()) {
            int c = choose % 2;
            if(pos - pre == mn[c]) {
                if(j) {
                    mn[c]--;
                }else {
                    j = true;
                }
                choose++;
                pre = pos;
            }
            q[pos++] = matrix[y][x];
            y += mov[choose % 4][0];
            x += mov[choose % 4][1];
        }
        return q;
    }
private:
    static constexpr int mov[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
};