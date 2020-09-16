#include <iostream>
using namespace std;

class Solution {
public:
    void InterAction() const;
private:
    bool CheckPasswd(const string& pwd) const;
};

void Solution::InterAction() const {
    string pwd;
    char choose;
    do {
       cout << "Please input password: ";
       cin >> pwd;
       if(CheckPasswd(pwd)){
           cout << "valid password\n";
       }else{
           cout << "invalid password\n";
       }
       cout << "Input again?[y/n]\n";
    }while (cin >> choose && choose == 'y');
}

bool Solution::CheckPasswd(const string &pwd) const {
    int cnt = 0;
    if(pwd.size() < 8)  return false;
    for(char c: pwd){
        if(c >= '0' && c <= '9'){
            cnt++;
        }else if(!(c >= 'a' && c <= 'z')){
            return false;
        }
    }
    if(cnt >= 2)    return true;
    else    return false;
}

int main() {
    Solution solve;

    solve.InterAction();

    return 0;
}