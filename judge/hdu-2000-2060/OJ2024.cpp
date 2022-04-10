#include<iostream>
#include<string>
using namespace std;
int main(){
    int a,count=0;
    while (cin >> a&&a)
    {
        string b;
        getchar();
        for(int i=0;i<a;i++){
            getline(cin,b);
            int jugde=1;
            if((b[0]>122||(b[0]<97&&b[0]>90)||b[0]<65)&&b[0]!='_'){
                jugde=0;
                goto r;
            }
            for(int j=0;j<b.size();j++){
                if((b[j]>122||(b[j]<97&&b[j]>90)||(b[j]<65&&b[j]>57)||b[j]<48)&&b[j]!='_'){
                    jugde=0;
                    break;
                }
            }
            r:
            if(jugde)
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        }   
    }
    return 0;
}