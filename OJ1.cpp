//集合:set
/*安迪的第一个字典
输入一个文本,找出所有不同的单词(连续的字母序列),按字典序从小到大输出,单词不区分大小写*/

#include<iostream>
#include<string>
#include<set>
#include<sstream>

using namespace std;

set<string> dict;

int main()
{
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    string temp,buf;
    while (cin >> temp)
    {
        for(int r=0;r<temp.size();r++)
            if(isalpha(temp[r])==0)
                temp[r]=0;
            else if(isalpha(temp[r])==1)
                temp[r]+=32;
        stringstream ss(temp);
        while (ss >> buf)   dict.insert(buf);
    }
    for(set<string>::iterator it = dict.begin();it!=dict.end();it++)
        cout << *it << endl;
}

