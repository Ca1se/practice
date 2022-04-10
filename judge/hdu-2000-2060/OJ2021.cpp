#include<iostream>
using namespace std;
int main(){
    int n,rmb[6]={100,50,10,5,2,1};
    while (cin >> n&&n)
    {
        int sum=0;
        for(int i=0;i<n;i++){
            int temp;
            cin >> temp;
            for(int j=0;j<6;j++){
                sum+=temp/rmb[j];
                temp-=rmb[j]*(temp/rmb[j]);
            }
        }
        cout << sum << endl;
    }
    return 0;
}