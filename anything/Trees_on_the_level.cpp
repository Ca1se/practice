/*UVa 122*/
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

struct cmp
{
    bool operator() (const string& a,const string& b){
        return a.size()!=b.size()?a.size()<b.size():a<b;
    }
};

int cnt=0;

int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w+",stdout);
    ios::sync_with_stdio(false);
    char a[500];
    set<string,cmp> p;
    map<string,string> fp;
    while(cin >> a){
        if(a[1]==')'){
            if(!cnt){
                for (auto it = p.begin(); it != p.end(); it++){
                    if ((*it).size()&&!count(p.begin(), p.end(), string((*it).begin(),(*it).end()-1))){
                        cnt++;
                        break;
                    }
                }
            }
            if(!cnt){
                for (auto it = p.begin(); it != p.end(); it++){
                    if (it != p.begin())    cout << " ";
                    cout << fp[*it];
                }
            }else{
                cout << "not complete";
            }
            cout << endl;
            p.clear();
            fp.clear();
            cnt=0;
        }else{
            string ts(strchr(a,',')+1,strchr(strchr(a,',')+1,')'));
            string ti(a+1,strchr(a,','));
            if(count(p.begin(),p.end(),ts))     cnt++;
            p.insert(ts);
            fp[ts]=ti;
        }
    }
    return 0;
}