/*Problem Description
输入n(n<=100)个整数，按照绝对值从大到小排序后输出。题目保证对于每一个测试实例，所有的数的绝对值都不相等。
 

Input
输入数据有多组，每组占一行，每行的第一个数字为n,接着是n个整数，n=0表示输入数据的结束，不做处理。
 

Output
对于每个测试实例，输出排序后的结果，两个数之间用一个空格隔开。每个测试实例占一行。
 
*/
#include<iostream>
#include<cstdlib>
#include<set>
using namespace std;
int main(){
    int n;
    while (cin >> n&&n)
    {
        set<int> a,b;
        for(int i=0;i<n;i++){
            int temp;
            cin >> temp;
            a.insert(abs(temp));
            b.insert(temp);
        }
        set<int>::iterator it=a.end();
        it--;
        for(int i=0;i<n;i++){
            if(i!=0)   cout << " ";
            if(b.count(*it))    cout << *it;
            else cout << -*it;
            it--;
        }
        cout << endl;
    }
    return 0;
}