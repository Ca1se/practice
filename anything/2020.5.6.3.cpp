#include<iostream>
#include<algorithm>
#include<cstring>
#define MAXN 25000+5
#define MAXT 1000000+5
using namespace std;
struct Shift
{
    int s;
    int e;
}shift[MAXN];
bool cmp(Shift x,Shift y){
    return x.s==y.s?x.e-x.s>y.e-y.s:x.s<y.s;
}
int main(){
    ios::sync_with_stdio(false);
    int N,T,cnt=1;
    char judge[MAXT];
    memset(judge,0,MAXT-1);
    cin >> N >> T;
    for(int i=0;i<N;i++){
        cin >> shift[i].s >> shift[i].e;
        memset(judge+shift[i].s,'x',shift[i].e-shift[i].s);
    }
    //判断是否能达到要求
    if(count(judge,judge+T,'x')!=T-1){
        cout << -1 << endl;
        return 0;
    }
    sort(shift,shift+N,cmp);
    int temp=shift[0].e,again=shift[0].s,count=0;
    for(int i=1;i<N;i++){
        if(shift[i].e==T){
            if(shift[i].s>temp){
                cnt+=2;
            }else if(shift[i].s<=temp){
                cnt++;
            }
            break;
        }
        if(shift[i].s!=again){
            again=shift[i].s;
            if(shift[i].s>temp){
                temp=shift[i].e;
                cnt+=2;
            }else if(shift[i].s==temp){
                temp=shift[i].e;
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}