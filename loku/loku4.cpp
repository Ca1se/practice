#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=2*1e5;
int num[maxn];
int main(){
    ios::sync_with_stdio(false);
    int n,max=-1;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> num[i];
    }
    sort(num,num+n-1);
    for(int i=0;i<n;i++){
        int temp=2*num[i],j;
        for(j=i+1;j<n&&num[j]<=temp;j++);
        max=(j-i)>max?(j-i):max;
    }
    cout << max << endl;
}