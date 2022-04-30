/*Problem Description
参加过上个月月赛的同学一定还记得其中的一个最简单的题目，就是{A}+{B}，那个题目求的是两个集合的并集，今天我们这个A-B求
的是两个集合的差，就是做集合的减法运算。（当然，大家都知道集合的定义，就是同一个集合中不会有两个相同的元素，这里还是提醒大家一下）

呵呵，很简单吧？
 

Input
每组输入数据占1行,每行数据的开始是2个整数n(0<=n<=100)和m(0<=m<=100),分别表示集合A和集合B的元素个数，
然后紧跟着n+m个元素，前面n个元素属于集合A，其余的属于集合B. 每个元素为不超出int范围的整数,元素之间有一个空格隔开.
如果n=0并且m=0表示输入的结束，不做处理。
 

Output
针对每组数据输出一行数据,表示A-B的结果,如果结果为空集合，则输出“NULL”,否则从小到大输出结果,为了简化问题，每个元素后面跟一个空格.*/
#include<iostream>
#include<set>
using namespace std;
int main(){
    int n,m;
    while (cin >> n >> m&&(n||m))
    {
        set<int> a;
        set<int> b;
        for(int i=0;i<n;i++){
            int temp;
            cin >> temp;
            a.insert(temp);
        }
        for(int i=0;i<m;i++){
            int temp;
            cin >> temp;
            b.insert(temp);
        }
        for(set<int>::iterator it=b.begin();it!=b.end();it++){
            if(a.count(*it))
                a.erase(a.find(*it));
        }
        if(a.size())
            for(set<int>::iterator it=a.begin();it!=a.end();it++){
                cout << *it << " ";
            }
        else
            cout << "NULL";
        cout << endl;
    }
    return 0;
}