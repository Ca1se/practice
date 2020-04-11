//集合:set
/*安迪的第一个字典
输入一个文本,找出所有不同的单词(连续的字母序列),按字典序从小到大输出,单词不区分大小写*/
/*
#include<iostream>
#include<string>
#include<set>
#include<sstream>

using namespace std;

set<string> dict;

int main()
{

    string temp,buf;
    while (cin >> temp)
    {
        for(int r=0;r<temp.size();r++)
            if(isalpha(temp[r]))    temp[r]=tolower(temp[r]); else temp[r]=' ';
        stringstream ss(temp);
        while (ss >> buf)   dict.insert(buf);
    }
    for(set<string>::iterator it = dict.begin();it!=dict.end();it++)
        cout << *it << endl;
    return 0;
}
*/

#include<iostream>
#include<string>
#include<set>
#include<sstream>
using namespace std;

set<string> dict;

int main()
{
    string s,buf;
    while (cin >> s)
    {
        for(int i=0;i<s.length();i++)
            if(isalpha(s[i]))   s[i]=tolower(s[i]); else  s[i]=' ';
        stringstream ss(s);
        while (ss >> buf)
        {
            dict.insert(buf);
        }
    }
    for(set<string>::iterator it=dict.begin();it!=dict.end();it++)
        cout << *it << endl;
    return 0;
}