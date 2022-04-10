#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isValidSerialization(string preorder) {
        if(preorder[0] == '#')  return (preorder.length() == 1);
        stack<int> s;
        int pos = preorder.find(',');
        if(pos++ == (size_t) -1)  return false;
        s.push(2);
        while(s.top() && pos < preorder.length()) {
            if(preorder[pos] == '#'){  
                s.push(s.top() - 1);
                pos++;
            }
            else if(preorder[pos] == ',' || pos == preorder.length() - 1)   s.push(s.top() + 1);
            pos++;
        } 
        return (pos == preorder.length() + 1 && s.top() == 0);
    }
    
};

int main() {
    Solution s;
    cout << s.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#") << endl;
    return 0;
}