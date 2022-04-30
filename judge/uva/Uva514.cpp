#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
int main(){
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdout);
    int n;
    while (cin >> n && n)
    {
        int train[1005];
        memset(train, 0, sizeof(train));
        for(int i = 0; cin >> train[i] && train[i]; i++){
            if(i == n - 1){
                stack<int> rail;
                bool goon = true;
                for(int j = 0,k = 1; k <= n || goon;){
                    if(k == train[j]){// ok
                        j++,k++;
                        goon = true;
                    }else{// not ok
                        if(!rail.empty() && rail.top() == train[j]){// rail has it
                            rail.pop();
                            j++;
                            goon = true;
                        }else{//rail dosent have it
                            if(k <= n){
                                rail.push(k);
                                k++;
                            }
                            goon = false;
                        }
                    }
                }
                if(rail.empty()){
                    cout << "Yes" << endl;
                }else{
                    cout << "No" << endl;
                }
                i = -1;
                memset(train, 0, sizeof(train));
            }
        }
        cout << endl;
    }
    return 0;
}