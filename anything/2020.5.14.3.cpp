#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;
bool cmp(int x, int y) {
    return x < y;
}
int main() {
    ios::sync_with_stdio(false);
    string a;
    while (cin >> a)
    {
        int number[1000], cnt = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == '5')   a[i] = ' ';
        }
        stringstream ss(a);
        while (ss >> number[cnt++]);//cnt循环完毕后=数的个数+2
        sort(number, number + cnt-1, cmp);
        for (int i = 0; i < cnt-1; i++) {
            if (i)   cout << " ";
            cout << number[i];
        }
        cout << endl;
    }
    return 0;
}