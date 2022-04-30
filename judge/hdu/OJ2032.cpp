/*Problem Description
还记得中学时候学过的杨辉三角吗？具体的定义这里不再描述，你可以参考以下的图形：
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
 

Input
输入数据包含多个测试实例，每个测试实例的输入只包含一个正整数n（1<=n<=30），表示将要输出的杨辉三角的层数。
 

Output
对应于每一个输入，请输出相应层数的杨辉三角，每一层的整数之间用一个空格隔开，每一个杨辉三角后面加一个空行。*/
#include<iostream>
using namespace std;
int main(){
    static int yanghui[35][35];
    yanghui[0][1]=1;
    int n,nax=-1;
    while (cin >> n&&n)
    {
        cout << 1 << endl;
        for(int i=1;i<n;i++){
            for(int j=1;j<i+2;j++){
                yanghui[i][j]=yanghui[i-1][j-1]+yanghui[i-1][j];
                if(j!=1)    cout << " ";
                cout << yanghui[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}