/*
Problem Description
输入两点坐标（X1,Y1）,（X2,Y2）,计算并输出两点间的距离。
 

Input
输入数据有多组，每组占一行，由4个实数组成，分别表示x1,y1,x2,y2,数据之间用空格隔开。
 

Output
对于每组输入数据，输出一行，结果保留两位小数。*/

#include<iostream>
#include<sstream>
#include<string>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    #if 0
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    #endif
    string str;
    while (getline(cin,str))
    {
        double a[4],a1,a2;
        stringstream ss(str);
        for(int i=0;i<4;i++)
            ss >> a[i];
        a1=a[0]-a[2];
        a2=a[1]-a[3];
        printf("%.2f\n",sqrt(a1*a1+a2*a2));
    }
}//菜