/*
Problem Description
统计给定的n个数中，负数、零和正数的个数。
 

Input
输入数据有多组，每组占一行，每行的第一个数是整数n（n<100），表示需要统计的数值的个数，然后是n个实数；如果n=0，则表示输入结束，该行不做处理。
 

Output
对于每组输入数据，输出一行a,b和c，分别表示给定的数据中负数、零和正数的个数。*/

#include<iostream>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        if(n==0)    break;
        int fs=0,l=0,zs=0;
        for(int i=0;i<n;i++)
        {
            double temp;
            cin >> temp;
            if(temp<0)
                fs++;
            else if (temp==0)
                l++;
            else
                zs++;
        }
        cout << fs << " " << l << " " << zs << endl;
    }
    return 0;
}