#include<iostream>
#include<set>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int n,m;
    while (cin >> n >> m&&n&&m)
    {
        int temp;
        set<int> a;
        for(int i=0;i<n;i++){
            cin >> temp;
            a.insert(temp);
        }
        set<int>::iterator it=--(a.end());
        for(int i=0;i<m;i++,it--){
            if(i)   cout << " ";
            cout << *it;
        }
        cout << "\n";
    }
    return 0;
}
