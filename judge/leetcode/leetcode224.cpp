class Solution {
public:
    int calculate(string s) {
        index = -1;
        return solve(s);
    }
private:
    int index;
    long long solve(const string& s) {
        long long sum = 0;
        int num = 0, c = 1, hasNum = 0;
        while(++index < s.length()) {
            if(s[index] >= '0' && s[index] <= '9') {
                num = num * 10 + (s[index] - '0');
                hasNum = 1;
            }else {
                if(hasNum) {
                    hasNum = 0;
                    sum += num * c;
                    c = 1;
                    num = 0;
                }
                if(s[index] == '-') c = -1;
                else if(s[index] == '(') {
                    sum += solve(s) * c;
                    c = 1;
                }else if(s[index] == ')') {
                    break;
                }
            }
        }
        sum += num * c;
        return sum;
    }
};  
