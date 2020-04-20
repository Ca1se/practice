#include<iostream>
#include<cstdlib>
using namespace std;
int main(){
    int m,n;
    while (cin >> m >> n&&m&&n)
    {
        int nm,nn,absmax=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int temp;
                cin >> temp;
                if(abs(temp)>abs(absmax)){
                    absmax=temp;
                    nm=i+1;
                    nn=j+1;
                }
            }
        }
        cout << nm << " " << nn << " " << absmax << endl;
    }
    return 0;
}