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
//分治
class Solution1 {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t m2 = 0b01010101010101010101010101010101;
        uint32_t m4 = 0b00110011001100110011001100110011;
        uint32_t m8 = 0b00001111000011110000111100001111;
        uint32_t m16 = 0b00000000111111110000000011111111;
        uint32_t m32 = 0b00000000000000001111111111111111;

        n = ((n & m2) << 1) | ((n & (m2 << 1)) >> 1);
        n = ((n & m4) << 2) | ((n & (m4 << 2)) >> 2);
        n = ((n & m8) << 4) | ((n & (m8 << 4)) >> 4);
        n = ((n & m16) << 8) | ((n & (m16 << 8)) >> 8);
        n = ((n & m32) << 16) | ((n & (m32 << 16)) >> 16);
        return n;
    }
};
