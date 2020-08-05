#include<iostream>
#include<cstring>
using namespace std;
int tree[1 << 20];

int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    int D,I; // 深度D, 小球个数I
    for(int i = 0; i < 1000 && cin >> D >> I; i++){
        memset(tree, 0, sizeof(tree));
        int step;
        for(int j = 0; j < I; j++){
            step = 1;
            while (step < (1 << D))
            {
                if(tree[step] == 0){
                    tree[step] = 1;
                    step = 2 * step;
                }else{
                    tree[step] = 0;
                    step = 2 * step + 1;
                }
            }
        }
        cout << step / 2 << endl;
    }
    return 0;
}