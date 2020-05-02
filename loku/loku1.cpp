#include<iostream>
using namespace std;
int main(){
    double m,n;
    while (cin >> m >> n)
    {
        double temp=m>n?n:m;
        cout << (long long)(m*n-temp) << endl;
    }
    return 0;
}