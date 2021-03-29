#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        int ori = 2147483648;
        for(int i = 0; i < 32; i++) {
            ans += (n & 1) * ori;
            n >>= 1;
            ori >>= 1;
        }
        return ans;
    }
};
