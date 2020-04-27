/*
例题6-1并行程序模拟 (Concurrency Simulator, ACMICPC World Finals 1991, UVa210)
你的任务是模拟n个程序(按输入顺序编号为1~n)的并行执行。每个程序包含不超过
25条语句，格式-共有5种: var = constant (赋值) ; print var (打印) ; lock; unlock; end.
变量用单个小写字母表示，初始为0，为所有程序公有(因此在一个程序里对某个变量
赋值可能会影响另一个程序)。常数是小于100的非负整数。
每个时刻只能有一个程序处于运行态，其他程序均处于等待态。上述5种语句分别需
要tl、t2、t3、t4、t5单位时间。运行态的程序每次最多运行Q个单位时间(称为配额)。
当一个程序的配额用完之后，把当前语句(如果存在)执行完之后该程序会被插入一个等
待队列中，然后处理器从队首取出一个程序继续执行。初始等待队列包含按输入顺序排列
的各个程序，但由于lock/unlock语句的出现，这个顺序可能会改变。
lock的作用是中申请对所有变量的独占访问。lock 和unlock总是成对出现，并且不会嵌
套。lock 总是在unlock的前面。当一个程序成功执行完 lock指令之后，其他程序一旦试图
执行lock指令，就会马上被放到一个所谓的阻止队列的尾部(没有用完的配额就浪费了)。
当unlock执行完毕后，阻止队列的第-一个程序进入等待队列的首部。
输入n,t1,t2,t3,t4,t5,Q以及n个程序，按照时间顺序输出所有print 语句的程序编号
和结果。*/

#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

struct Queue {
    string command;
    Queue* next;
};
Queue* head[2];//0为等待队列,1为阻止队列
Queue* tail[2];
void inqueue(string str) {
    Queue* newqu;
    newqu = new Queue;
    newqu->command = str;
    if (head[0] == NULL) {
        head[0] = newqu;
        tail[0] = newqu;
        newqu->next = NULL;
    }
    else {
        tail[0]->next = newqu;
        tail[0] = newqu;
        newqu->next = NULL;
    }
}

string outqueue() {
    Queue* target = head[0];
    string temp = target->command;
    head[0] = head[0]->next;
    delete target;
    return temp;
}

Queue* findend(Queue*& ahead)
{
    Queue* target;
    target = ahead;
    while ((target->command)[2]!='d')
        target = target->next;
    return target;
}

void movetostop() {
    Queue* endp, * temp;
    temp = head[0];
    endp = findend(head[0]);
    head[0] = endp->next;
    endp->next = NULL;
    if (head[1] == NULL) {
        head[1] = temp;
        tail[1] = endp;
    }
    else {
        tail[1]->next = temp;
        tail[1] = endp;
    }
}

void movetowait(int &timecount) {
    if (head[1] == NULL)   return;
    timecount=0;
    Queue* endp, * temp;
    endp = findend(head[1]);
    temp = head[1];
    head[1] = endp->next;
    endp->next = head[0];
    head[0] = temp;
}

void movetotail() {
    Queue* endp, * temp;
    endp = findend(head[0]);
    if (endp->next == NULL)
        return;
    temp = head[0];
    head[0] = endp->next;
    endp->next = NULL;
    tail[0]->next = temp;
    tail[0] = endp;
}

int main()
{
#if 1
    freopen("compli/test.in", "r", stdin);
    freopen("compli/test.out", "w", stdout);
#endif
    int N;
    scanf("%d%*c",&N);
    while (N--)
    {
        int n, t1, t2, t3, t4, t5, Q, islocked = 0, timecount = 0, count = 1;
        scanf("%*c%d %d %d %d %d %d %d%*c",&n,&t1,&t2,&t3,&t4,&t5,&Q);
        map<string, string> var;
        string str;
        while (getline(cin, str))
        {
            if(str=="") break;
            if (str == "end")
                str += to_string(count++);
            inqueue(str); //head[0]为等待队列
        }
        while (head[0] != NULL)
        {
            string temp;
            temp = outqueue();
            if (temp[2]=='i')
            {
                //执行print语句
                timecount += t2;
                stringstream ss(temp);
                string as;
                ss >> as >> as;
                Queue *endp = findend(head[0]);
                if (var.count(as))
                    printf("%d: %d\n",(endp->command)[3]-48,atoi(var[as].c_str()));
                else
                    printf("%d: %d\n",(endp->command)[3]-48,0);
            }
            else if (temp[2]=='c')
            {
                //执行lock
                timecount += t3;
                if (islocked == 1)
                {
                    timecount = 0;
                    movetostop();
                    continue;
                }
                islocked = 1;
            }
            else if (temp[2]=='l')
            {
                //执行unlock
                timecount += t4;
                islocked = 0;
                movetowait(timecount);
                continue;
            }
            else if (temp[2]=='d')
            {
                //执行end
                timecount = 0;
                continue;
            }
            else
            {
                //执行var = r
                timecount += t1;
                stringstream ss(temp);
                string as1, as2;
                ss >> as1 >> as2 >> as2;
                var[as1] = as2;
            }
            if (timecount >= Q)
            {
                timecount = 0;
                movetotail();
            }
        }
        if(N)   puts("");
    }
    return 0;
}