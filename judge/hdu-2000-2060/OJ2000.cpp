/*
Problem Description
输入三个字符后，按各字符的ASCII码从小到大的顺序输出这三个字符。
Input
输入数据有多组，每组占一行，有三个字符组成，之间无空格。
Output
对于每组输入数据，输出一行，字符中间用一个空格分开。
*/
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
    
int main()
{
    #if 0
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    #endif
    string a;
    while (cin >> a)
    {
        sort(a.begin(),a.end());
        for(int i=0;i<3;i++)
        {
            cout << a[i];
            if(i<2) cout << " ";
        }
        cout << endl;
    }   
}