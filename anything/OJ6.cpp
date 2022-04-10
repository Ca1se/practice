/*  UVa 514
    某城市有一个火车站,铁轨铺设如图所示.有n接车厢从A方向驶入车站,按近站顺序编号为1-n.
    你的人物时判断是否能让它们按照某种特定的顺序进入B方向的铁轨并使出车站.例如,出栈顺序(54123)是不可能的,但(54321)是可能的.
    为了重组车厢,你可以借助中转站C.这是一个可以停放容易多杰车厢的车站,但由于末端封顶,驶入C的车厢必须按照相反的顺序驶出车站C.*/
    //  别人的*/
#include <cstdio>
#include <stack>
using namespace std;
const int MAXN = 1010;

int n, target[MAXN];

int main()
{
    while (scanf("%d", &n) == 1&&n)
    {
        while (1)
        {
            stack<int> s;
            int A = 1, B = 1,jugde=1;
            for (int i = 1; i <= n; i++)
            {
                scanf("%d", &target[i]);
                if(target[i]==0)
                {
                    jugde=0;
                    break;
                }
            }
            if(jugde==0)
                break;
            int ok = 1;
            while (B <= n)
            {
                if (A == target[B])
                {
                    A++;
                    B++;
                }
                else if (!s.empty() && s.top() == target[B])
                {
                    s.pop();
                    B++;
                }
                else if (A <= n)
                    s.push(A++);
                else
                {
                    ok = 0;
                    break;
                }
            }
            printf("%s\n", ok ? "Yes" : "No");
        }
        printf("\n");
    }
    return 0;
}