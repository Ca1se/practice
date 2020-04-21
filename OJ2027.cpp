/*Problem Description
统计每个元音字母在字符串中出现的次数。
 

Input
输入数据首先包括一个整数n，表示测试实例的个数，然后是n行长度不超过100的字符串。
 

Output
对于每个测试实例输出5行，格式如下：
a:num1
e:num2
i:num3
o:num4
u:num5
多个测试实例之间由一个空行隔开。

请特别注意：最后一块输出后面没有空行：）*/
#include<iostream>
#include<string>
using namespace std;
int main(){
    int n;
    cin >> n;
    getchar();
    for (int i = 0; i < n; i++)
    {
        string temp;
        int count[5] = {0, 0, 0, 0, 0};
        getline(cin, temp);
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j] == 'a')
                count[0]++;
            else if (temp[j] == 'e')
                count[1]++;
            else if (temp[j] == 'i')
                count[2]++;
            else if (temp[j] == 'o')
                count[3]++;
            else if (temp[j] == 'u')
                count[4]++;
        }
        if(i)   cout << endl;
        char y[6] ="aeiou";
        for(int i=0;i<5;i++){
            cout << y[i] << ':' << count[i] << endl;
        }
    }
    return 0;
}
