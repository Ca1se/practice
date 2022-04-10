#include<iostream>
#include<string>
using namespace std;
int main(){
    string a;
    while (cin >> a)
    {
        char nax=0;
        int temp=a.size();
        for(int i=0;i<temp;i++){
            if(a[i]>nax)
                nax=a[i];
        }
        for(int i=temp-1;i>-1;i--){
            if(a[i]==nax)
                a.insert(i+1,"(max)");
        }
        cout << a << endl;
    }
    return 0;
}