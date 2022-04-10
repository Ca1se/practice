/*Problem Description
统计给定文本文件中汉字的个数。
 

Input
输入文件首先包含一个整数n，表示测试实例的个数，然后是n段文本。
 

Output
对于每一段文本，输出其中的汉字的个数，每个测试实例的输出占一行。

[Hint:]从汉字机内码的特点考虑~*/
#include<iostream>
#include<string>
using namespace std;
int main(){
    int n;
    while (cin >> n&&n)
    {
        getchar();
        for(int i=0;i<n;i++){
            string temp;
            int count=0;
            getline(cin,temp);
            for(int j=0;j<temp.size();j++){
                if(temp[j]>=0)   count++;
            }
            cout << (temp.size()-count)/2 << endl;
        }
    }
    return 0;
}