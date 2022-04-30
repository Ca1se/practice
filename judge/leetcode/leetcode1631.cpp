//主要的麻烦点在每条路的代价是整条路上的每相邻两点差值的最大值
//普通搜索能过但较慢
//把寻找最大差值最小的路变成能否找出一条路使这条路上每相邻节点差值最大值不超过x
//然后二分查找这个x


#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int hx = heights[0].size(); int hy = heights.size();
        bool vis[hy][hx];
        int minn = 0; int maxx = 1e6 - 1; int ans = 0;
        while(maxx >= minn) {
            int mid = (maxx + minn) / 2;
            memset(vis, 0, sizeof(vis));
            queue<pair<int, int>> q;
            q.emplace(0, 0);
            vis[0][0] = true;
            while(!q.empty()) {
                auto it = q.front(); q.pop();
                if(it.first == hx - 1 && it.second == hy - 1)    break;
                for(int i = 0; i < 4; i++) {
                    int x = it.first + op[i][0]; int y = it.second + op[i][1];
                    if(x > -1 && x < hx && y > -1 && y < hy && !vis[y][x] && abs(heights[y][x] - heights[it.second][it.first]) <= mid) {
                        q.emplace(x, y);
                        vis[y][x] = true;
                    }
                }
            }
            if(vis[hy - 1][hx - 1]) {
                ans = mid;
                maxx = mid - 1;
            }else {
                minn = mid + 1;
            }
        }
        return ans;
    }
private:
    static constexpr int op[4][2] = {0, -1, 1, 0, 0, 1, -1, 0};
};