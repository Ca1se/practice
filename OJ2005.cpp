/*
Problem Description
给定一个日期，输出这个日期是该年的第几天。
 

Input
输入数据有多组，每组占一行，数据格式为YYYY/MM/DD组成，具体参见sample input ,另外，可以向你确保所有的输入数据是合法的。
 

Output
对于每组输入数据，输出一行，表示该日期是该年的第几天。*/
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main()
{
    #if 0
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    #endif
    string date;
    while (cin >> date)
    {
        int monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        int year,month,day,ans=0;
        for(int i=0;i<date.size();i++)
            if(date[i]=='/')
                date[i]=' ';
        stringstream ss(date);
        ss >> year >> month >> day;
        if((year%4==0&&year%100!=0)||(year%100==0&&year%400==0))
            monthday[1]=29;
        for(int i=0;i<month-1;i++)
            ans+=monthday[i];
        ans+=day;
        cout << ans << endl;
    }// wssb
}//把调试语句删掉