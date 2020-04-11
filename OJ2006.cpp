/*Problem Description
给你n个整数，求他们中所有奇数的乘积。
 

Input
输入数据包含多个测试实例，每个测试实例占一行，每行的第一个数为n，表示本组数据一共有n个，接着是n个整数，你可以假设每组数据必定至少存在一个奇数。
 

Output
输出每组数中的所有奇数的乘积，对于测试实例，输出一行。*/
#include<iostream>
#include<vector>
using namespace std;

vector<int> a;
int main()
{
    int str;
    while (cin >> str)
    {
        int ans=1;
        for(int i=0;i<str;i++)
        {
            int temp;
            cin >> temp;
            a.push_back(temp);
        }
        for(int i=0;i<a.size();i++)
            if(a[i]/2*2!=a[i])
                ans*=a[i];
        cout << ans << endl;
        a.erase(a.begin(),a.end());
    }
}