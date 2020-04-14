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
#include <cstdlib>
#include <string>
#include <map>
#include <sstream>
using namespace std;
map<string,string> var;

struct Queue
{
    string command;
    Queue* next;
};
Queue* head[2];
Queue* tail[2];
void inqueue(Queue* &head,int marl,string str)
{
    Queue* newqu=(Queue*)malloc(sizeof(Queue));
    newqu->command=str;
    if(head==NULL)
    {
        head=newqu;
        tail[marl]=newqu;
        newqu->next=NULL;
    }
    else
    {
        tail[marl]->next=newqu;
        tail[marl]=newqu;
        newqu->next=NULL;
    }
}

string outqueue(Queue* &head)
{
    Queue* target;
    target=head;
    string temp;
    temp=head->command;
    head=head->next;
    free(target);
    return temp;
}

Queue* findend(Queue* &head)
{
    Queue* target;
    target=head;
    while (target->command!="end")
        target=target->next;
    return target;
}
int main()
{
    #if 1
    freopen("compli/test.in","r",stdin);
    freopen("compli/test.out","w",stdout);
    #endif
    int n,t1,t2,t3,t4,t5,Q,count=0,islocked=0,timecount=0;
    cin >> n >> t1 >> t2 >> t3 >> t4 >> t5 >> Q;
    string str;
    while (getline(cin,str))
        inqueue(head[0],0,str);
    while (1)
    {
        if(timecount<Q&&head[0]!=NULL)
        {
            string temp = outqueue(head[0]);
            inqueue(head[1], 1, temp);
            if (temp.find("print ") < 1000)
                timecount += t2;
            else if (temp == "lock")
                timecount += t3;
            else if (temp == "unlock")
                timecount += t4;
            else if (temp == "end")
                timecount += t5;
            else
                timecount += t1;
        }
        else
        {
            if(head[1]==NULL)
            {
                if(head[0]==NULL)
                    break;
                timecount=0;
                continue;
            }
            string temp = outqueue(head[1]);
            if(temp.find("print ")>1000)
            {
                string as1;
                stringstream ss(temp);
                ss >> as1 >> as1;
                if(var.count(as1))
                    cout << atoi(var[as1].c_str()) << "\n";
                else
                    cout << 0 << "\n";
            }
            else if(temp == "lock")
            {
                if(islocked==0)
                    islocked=1;
                else
                {
                    timecount=0;
                    Queue* temptr;
                    temptr=findend(head[1]);
                    tail[1]->next=head[1];
                    head[1]=temptr->next;
                    temptr->next=NULL;
                }
            }
            else if(temp == "unlock")
            {
                islocked=0;
                Queue* temptr,*temptr1;
                temptr1=head[0];
                temptr=findend(head[0]);
                head[0]=temptr->next;
                temptr->next=head[1];
                head[1]=temptr1;
            }
            else if(temp == "end")
                ;
            else
            {
                string as1,as2;
                stringstream ss(temp);
                ss >> as1 >> as2 >> as2;
                var[as1]=as2;
            }
        }
    }
    
}