#include<iostream>
#include<cstring>
using namespace std;
/*
int tree[1 << 20];

//对于编号为n的节点, 它的左子节点编号为n * 2, 它的右子节点编号为n * 2 + 1

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
}*/

//直接模拟最后一个球
//对于经过某节点的第n个球, 如果n是奇数, 则球会向左子节点走且是第(n + 1) / 2个经过左子节点的,
//如果n是偶数, 则球会向右子节点走且是第n / 2个经过右子节点的
int main() {
    int D, I, n;
    while(scanf("%d", &n) == 1 && n != -1) {
        for(int j = 0; j < n && scanf("%d%d", &D, &I); j++) {
            int k = 1;
            for(int i = 0; i < D - 1; i++) {
                if(I % 2) {
                    k *= 2;
                    I = (I + 1) / 2;
                }else {
                    k = k * 2 + 1;
                    I /= 2;
                }
            }
            printf("%d\n", k);
        }
    }
    return 0;
}