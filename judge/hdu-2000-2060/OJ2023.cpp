#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    int n,m;
    while (cin >> n >> m&&n&&m)
    {
        double a[50][5];
        double avg[5];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                cin >> a[i][j];
        }
        for(int i=0;i<n;i++){
            double sum=0;
            for(int j=0;j<m;j++)
                sum+=a[i][j];
            if(i)   cout << " ";
            printf("%.2f",sum/m);
        }
        cout << endl;
        for(int i=0;i<m;i++){
            double sum=0;
            for(int j=0;j<n;j++)
                sum+=a[j][i];
            if(i)   cout << " ";
            printf("%.2f",sum/n);
            avg[i]=sum/n;
        }
        cout << endl;
        int count=0;
        for(int i=0;i<n;i++){
            int judge=1;
            for(int j=0;j<m;j++){
                if(a[i][j]<avg[j]){
                    judge=0;
                    break;
                }
            }
            if(judge)   count++;
        }
        cout << count << endl << endl;
    }
    return 0;
}