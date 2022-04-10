#include<iostream>
#include<cstring>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int mark[1000];
    memset(mark,0,sizeof(mark));//不能写1000,必须用sizeof()
    int cnt1,cnt2,x,y,i,j,count=0;
    cin >> cnt1 >> cnt2 >> x >> y;
    for(j=0;count<cnt1;j++){
        if((j+1)%x){
            count++;
            mark[j]++;
        }
    }
    for(i=0;cnt2;i++){
        if(mark[i])     continue;
        else if((i+1)%y)    cnt2--;
        else if(cnt1&&(i+1)%x){
                cnt1--;
                cnt2--;
        }
    }
    cout << (i>j?i:j) << endl;
    return 0;
}