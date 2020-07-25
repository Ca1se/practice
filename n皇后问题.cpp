/*输入N,输出在NxN棋盘上放置N个皇后,且使其不相互攻击的方案数*/
#include <iostream>
using namespace std;
int ans=0, ende;
void queenplan(int row, int ld, int rd)
{
    int pos, p;
    if (row != ende){
        pos = ende & (~(row | ld | rd));
        while (pos){
            p = pos & (~pos + 1);
            pos -= p;
            queenplan(p | row, (p | ld) << 1, (p | rd) >> 1);
        }
    }else{
        ans++;
    }
}
int main()
{
    int N;
    cin >> N;
    ende = (1 << N) - 1;
    queenplan(0, 0, 0);
    cout << ans << endl;
}