#include<iostream>
using namespace std;
static int Beehive[3200][1600];
int n,nax=0,cot=0;
void findhappynax(int i,int j,int sum){
    if(i+1<4*n-3&&j-1>-1&&Beehive[i+1][j-1]!=0)
        findhappynax(i+1,j-1,sum+Beehive[i][j]-2000);
    if(i+2<4*n-3&&Beehive[i+2][j]!=0)
        findhappynax(i+2,j,sum+Beehive[i][j]-2000);
    if(i+1<4*n-3&&j+1<2*n-1&&Beehive[i+1][j+1]!=0)
        findhappynax(i+1,j+1,sum+Beehive[i][j]-2000);
    if(i==4*n-4&&j==n-1){
        sum+=Beehive[i][j]-2000;
        if(cot){
            if(sum>nax){
                nax=sum;
            }

        }else{
            cot++;
            nax=sum;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    int now=n-1;
    for(int i=0;i<n-1;i++,now--)
        for(int j=now,k=0;k<i+1;j+=2,k++){
            cin >> Beehive[i][j];
            Beehive[i][j]+=2000;
        }
    now=0;
    for(int i=n-1;i<3*n-2;i++,now=!now){
        for(int j=now,k=0;k<(now?n-1:n);j+=2,k++){
            cin >> Beehive[i][j];
            Beehive[i][j]+=2000;
        }
    }
    now=1;
    for(int i=3*n-2;i<4*n-3;i++,now++){
        for(int j=now,k=0;k<4*n-4-i+1;j+=2,k++){
            cin >> Beehive[i][j];
            Beehive[i][j]+=2000;
        }
    }
    findhappynax(0,n-1,0);
    cout << nax << "\n";
    return 0;
}