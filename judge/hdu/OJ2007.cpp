/*
Problem Description
给定一段连续的整数，求出他们中所有偶数的平方和以及所有奇数的立方和。
 

Input
输入数据包含多组测试实例，每组测试实例包含一行，由两个整数m和n组成。
 

Output
对于每组输入数据，输出一行，应包括两个整数x和y，分别表示该段连续的整数中所有偶数的平方和以及所有奇数的立方和。
你可以认为32位整数足以保存结果。*/

#include<iostream>
using namespace std;

int main()
{
    #if 0
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    #endif
    int a,b;
    while (cin >> a >> b)
    {
        int s=0,x=0;
        for(int i=(a<b?a:b);i<(a<b?b:a)+1;i++)
            if(i/2*2==i)
                s+=i*i;
            else   
                x+=i*i*i;
        cout << s << " " << x << endl;
    }
    
}