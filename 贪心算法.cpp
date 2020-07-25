/*【背包问题】有一个背包，容量是M=150，有7个物品，物品可以分割成任意大小。要求尽可能让装入背包中的物品总价值最大，但不能超过总容量。
物品：A  B  C  D  E  F  G
重量：35 30 60 50 40 10 25
价值：10 40 30 50 35 40 30
f 
*/
#include<iostream>
#include<map>
#include<string>
#include<algorithm>


using namespace std;

map<double,char> a;
map<double,double> b;

bool cmp(double i,double j){
    return (i>j);
}

int main(){
    ios::sync_with_stdio(false);
    char stuff[8]="ABCDEFG";
    double q[7];
    double p[7];
    for(int i=0;i<7;i++){
        cin >> q[i];
        p[i]=q[i];
    }
    for(int i=0;i<7;i++){
        double temp;
        cin >> temp;
        q[i]=temp/q[i]-q[i]*0.00000001;
        a.insert(pair<double,char>(q[i],stuff[i]));
        b.insert(pair<double,double>(q[i],p[i]));
    }
    sort(q,q+7,cmp);
    double sum=0;
    for(int i=0;i<7;i++){
        if(sum+b[q[i]]<=150){
            sum+=b[q[i]];
            cout << a[q[i]] << endl;
        }
    }
}