class Solution {
public:
    int clumsy(int N) {
        long ans = 0;
        int tmp = N < 4 ? 1 : -1;
        switch (N % 4) {
            case 3: {
                ans += 6 * tmp;
                break;
            }
            case 2: {
                ans += 2 * tmp;
                break;
            }
            case 1: {
                ans += tmp;
                break;
            }
        }
        if(N >= 4) {
            ans += N * (N - 1) / (N - 2) + (N - 3);
            N -= 4;
            int n = N;
            for(int i = 0; i < n / 4; i++) {
                ans -= N * (N - 1) / (N - 2) - (N - 3);
                N -= 4;
            }
        }
        return ans;
    }
};