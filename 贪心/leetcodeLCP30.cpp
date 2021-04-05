class Solution {
public:
    int magicTower(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> q;
        long b = 1, wait = 0, cnt = 0;
        for(int i : nums) {
            if(i >= 0)  b += i;
            else {
                cnt++;
                if(b + i > 0) {
                    b += i;
                    q.push(i);
                }else {
                    if(!q.empty() && q.top() < i) {
                        b = b - q.top() + i;
                        wait += q.top();
                        q.pop();
                        q.push(i);
                    }else {
                        wait += i;
                    }
                }
            }
        }
        if(b + wait > 0)    return cnt - q.size();
        else    return -1;
    }
};