#include<iostream>
#include<algorithm>
using namespace std;
struct Tvprogram
{
    int s,e;
}tvprogram[100];

bool cmp(Tvprogram x,Tvprogram y){
    return x.e<y.e;
}

int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    int n;
    while (cin >> n && n)
    {
        for(int i=0;i<n;i++){
            cin >> tvprogram[i].s >> tvprogram[i].e;
        }
        sort(tvprogram,tvprogram+n,cmp);
        int te=-1,cnt=0;
        for(int i=0;i<n;i++){
            if(tvprogram[i].s>=te){
                te=tvprogram[i].e;
                cnt++;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}