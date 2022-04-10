class Solution {
public:
    bool isUgly(int n) {
        if(n == 1)  return true;
        else if(n < 1)  return false;
        const int mod[] = {5, 3, 2};
        int pos = 0;
        while(pos <= 2 && n != 1) {
            if(n % mod[pos]) pos++;
            else n = n / mod[pos];
        }
        return pos <= 2;
    }
};