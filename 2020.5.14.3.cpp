#include<iostream>
#include<set>
#include<sstream>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    set<int> t;
    string a;
    while (cin >> a)
    {
        int temp;
        for(int i=0;i<a.size();i++){
            if(a[i]=='5')   a[i]=' ';
        }
        stringstream ss(a);
        while (ss >> temp)
        {
            t.insert(temp);    
        }
        for(set<int>::iterator it=t.begin();it!=t.end();it++){
            if(it!=t.begin())   cout << " ";
            cout << *it;
        }
        cout << endl;
    }
    return 0;
}