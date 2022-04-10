#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct Data
{
    string place;
    string fruit;
    int sum;
};

bool cmp(Data x,Data y){
    return x.place==y.place?x.fruit<y.fruit:x.place<y.place;
}

int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w+",stdout);
    ios::sync_with_stdio(false);
    Data* data;
    int n,m;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> m;
        Data data[100];
        int cnt=0;
        for(int j=0;j<m;j++){
            string temps[2];
            int tempi,k;
            cin >> temps[1] >> temps[0] >> tempi;
            for(k=0;k<cnt;k++){
                if(data[k].place==temps[0] && data[k].fruit==temps[1]){
                    data[k].sum+=tempi;
                    break;
                }
            }
            if(k==cnt){
                data[cnt].place=temps[0];
                data[cnt].fruit=temps[1];
                data[cnt++].sum=tempi;
            }
            sort(data,data+cnt,cmp);
        }
        string mark="";
        for(int j=0;j<cnt;j++){
            if(data[j].place!=mark){
                mark=data[j].place;
                cout << data[j].place << endl;
            }
            cout << "   |----" << data[j].fruit << "(" << data[j].sum << ")\n";
        }
    }
    return 0;
}