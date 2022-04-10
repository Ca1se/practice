/*Problem Description
有一头母牛，它每年年初生一头小母牛。每头小母牛从第四个年头开始，每年年初也生一头小母牛。请编程实现在第n年的时候，共有多少头母牛？
 

Input
输入数据由多个测试实例组成，每个测试实例占一行，包括一个整数n(0<n<55)，n的含义如题目中描述。
n=0表示输入数据的结束，不做处理。
 

Output
对于每个测试实例，输出在第n年的时候母牛的数量。
每个输出占一行。*/
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    while (cin >> n&&n)
    {
        vector<int> a(1,4);
        for(int i=0;i<n-1;i++){
            for(int j=0;j<a.size();j++){
                if(a[j]>=3) a.push_back(0);
                a[j]++;
            }
        }
        cout << a.size() << endl;
    }
    return 0;
}