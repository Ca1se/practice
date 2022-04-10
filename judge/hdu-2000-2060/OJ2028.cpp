/*Problem Description
求n个数的最小公倍数。
 

Input
输入包含多个测试实例，每个测试实例的开始是一个正整数n，然后是n个正整数。
 

Output
为每组测试数据输出它们的最小公倍数，每个测试实例的输出占一行。你可以假设最后的输出是一个32位的整数。*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int n;
    while (cin >> n&&n)
    {
        vector<int> a;
        for(int i=0;i<n;i++){
            int temp;
            cin >> temp;
            a.push_back(temp);
        }
        auto nax=max_element(a.begin(),a.end());
        for(int i=*nax;;i++){
            int judge=1;
            for(int j=0;j<a.size();j++){
                if(i%a[j]!=0){
                    judge=0;
                    break;
                }
            }
            if(judge){
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}