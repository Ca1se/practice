/*Problem Description
求实数的绝对值。
 

Input
输入数据有多组，每组占一行，每行包含一个实数。
 

Output
对于每组输入数据，输出它的绝对值，要求每组数据输出一行，结果保留两位小数。*/
#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
    double a;
    while (cin >> a)
    {
        printf("%.2f\n",a>0?a:-a);
    }
    
}