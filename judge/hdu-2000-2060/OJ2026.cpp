/*Problem Description
输入一个英文句子，将每个单词的第一个字母改成大写字母。
 

Input
输入数据包含多个测试实例，每个测试实例是一个长度不超过100的英文句子，占一行。
 

Output
请输出按照要求改写后的英文句子。*/
#include<iostream>
#include<string>
using namespace std;
int main(){
    string a;
    while (getline(cin,a))
    {
        a[0]+=(a[0]-97)>=0?-32:0;
        for(int i=1;i<a.size();i++){
            if(a[i]==' '&&a[i+1]-97>=0)
                a[i+1]-=32;
        }
        cout << a << endl;
    }
    return 0;
}