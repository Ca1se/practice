#include<iostream>
using namespace std;
int main() {
    int test;
    cin >> test;
    for(int k = 0; k < test; k++){
        double p;
        cin >> p;
        if(p > 1){// A 是2x
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
        }
    }
    return 0;
}