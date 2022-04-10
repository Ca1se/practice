/*
Problem Description
青年歌手大奖赛中，评委会给参赛选手打分。选手得分规则为去掉一个最高分和一个最低分，然后计算平均得分，请编程输出某选手的得分。
 

Input
输入数据有多组，每组占一行，每行的第一个数是n(2<n<=100)，表示评委的人数，然后是n个评委的打分。
 

Output
对于每组输入数据，输出选手的得分，结果保留2位小数，每组输出占一行。*/
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    int n;
    while (cin >> n)
    {
        int count=0;
        double temp,sum=0,nax=-1,nin=1000,num[200];
        for(int i=0;i<n;i++){
            cin >> num[i];
            if(num[i]>nax)  nax=num[i];
            if(num[i]<nin)  nin=num[i];
        }
        for(int i=0;i<n;i++){
            if(num[i]==nax){
                num[i]=-1;
                break;
            }
        }
        for(int i=0;i<n;i++){
            if(num[i]==nin){
                num[i]=-1;
                break;
            }
        }
        for(int i=0;i<n;i++)
            if(num[i]!=-1)
                sum+=num[i];
        printf("%.2f\n",sum/(n-2));
    }
    return 0;
}