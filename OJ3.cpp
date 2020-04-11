//映射:map
/*反片语
输入一些单词,找出所有满足如下条件的单词:该单词不能通过字母重排,得到输入文本中的另外一个单词.
在判断是否满足条件时,字母不分大小写,但在输出时因保留输入中的大小写,按字典序进行排列(所有大写字母在所有小写字母的前面)
输入以 # 结尾
*/
/*
#include<iostream>
#include<string>
#include<vector>
#include<set>

#define ll long long
using namespace std;

vector<ll> ax,as;
vector<string> str;
set<string> s;

int main()
{
    #if 0
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    #endif
    string temp;
    while (cin >> temp)
    {
        if(temp=="#")   break;
        int judge=0;
        ll temp1=1,temp2=0;
        for(int i=0;i<temp.size();i++)
        {
            temp1*=(temp[i]-97)<0?temp[i]-64:temp[i]-96;
            temp2+=(temp[i]-97)<0?temp[i]-64:temp[i]-96;
        }
        for(int i=0;i<ax.size();i++)
        {
            if(ax[i]==temp1&&as[i]==temp2)
            {
                judge=1;
                str[i]="\0";
                break;
            }
        }
        if(judge!=1)
        {
            ax.push_back(temp1);
            as.push_back(temp2);
            str.push_back(temp);
        }
    }
    for(int i=0;i<str.size();i++)
        if(str[i]!="\0")
            s.insert(str[i]);
    for(set<string>::iterator it=s.begin();it!=s.end();it++)
        cout << *it << endl;
    return 0;
}*/

#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

map<string,int> cnt;
vector<string> words;

string forma(string str)
{
    for(int i=0;i<str.size();i++)
        str[i]=tolower(str[i]);
    sort(str.begin(),str.end());
    return str;
}

int main()
{
    #if 1
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
    #endif
    string temp;
    while (cin >> temp)
    {
        if(temp[0]=='#')    break;
        words.push_back(temp);
        string s=forma(temp);
       // cout << "!!" << s << endl;
        if(!cnt.count(s))   cnt[s]=0;
        cnt[s]++;
     //   cout << cnt[s] << endl;
    }
    vector<string> ans;
    for(int i=0;i<words.size();i++)
        if(cnt[forma(words[i])]==1)     ans.push_back(words[i]);
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)
        cout << ans[i] << endl;
}