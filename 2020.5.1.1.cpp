#include<iostream>
#include<cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int l,r,k;
    while (cin >> l >> r >> k)
    {
        if(k==1){
            cout << "Draw" << "\n";
            continue;
        }
        int sum=0;
        for(int i=l;i<r+1;i++)
            sum+=(int)(log(i)/log(k))+1;
        if(sum%2)   cout << "刘明" << "\n";
        else    cout << "马克" << "\n";
    }
    return 0;
}