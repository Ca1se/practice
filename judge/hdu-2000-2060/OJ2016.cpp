/*
Problem Description
输入n(n<100)个数，找出其中最小的数，将它与最前面的数交换后输出这些数。
 

Input
输入数据有多组，每组占一行，每行的开始是一个整数n，表示这个测试实例的数值的个数，跟着就是n个整数。n=0表示输入的结束，不做处理。
 

Output
对于每组输入数据，输出交换后的数列，每组输出占一行。*/
#include<iostream>
#include<string>
using namespace std;
int main(){
    int n;
    while (cin >> n&&n)
    {
        int a[200],nin=1000,r;
        for(int i=0;i<n;i++){
            cin >> a[i];
            if(a[i]<nin){
                r=i;
                nin=a[i];
            }
        }
        int temp=a[r];
        a[r]=a[0];
        a[0]=temp;
        for(int i=0;i<n;i++){
            if(i!=0)    cout << " ";
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}