/*Problem Description
“今年暑假不AC？”
“是的。”
“那你干什么呢？”
“看世界杯呀，笨蛋！”
“@#$%^&*%...”

确实如此，世界杯来了，球迷的节日也来了，估计很多ACMer也会抛开电脑，奔向电视了。
作为球迷，一定想看尽量多的完整的比赛，当然，作为新时代的好青年，你一定还会看一些其它的节目，比如新闻联播（永远不要忘记关心国家大事）、非常6+7、
超级女生，以及王小丫的《开心辞典》等等，假设你已经知道了所有你喜欢看的电视节目的转播时间表，你会合理安排吗？（目标是能看尽量多的完整节目）
 

Input
输入数据包含多个测试实例，每个测试实例的第一行只有一个整数n(n<=100)，表示你喜欢看的节目的总数，然后是n行数据，
每行包括两个数据Ti_s,Ti_e (1<=i<=n)，分别表示第i个节目的开始和结束时间，为了简化问题，每个时间都用一个正整数表示。n=0表示输入结束，不做处理。
 

Output
对于每个测试实例，输出能完整看到的电视节目的个数，每个测试实例的输出占一行。*/
#include<iostream>
#include<algorithm>
using namespace std;
struct Tvprogram
{
    int s,e;
}tvprogram[100];

bool cmp(Tvprogram x,Tvprogram y){
    return x.e<y.e;
}

int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n)
    {
        for(int i=0;i<n;i++){
            cin >> tvprogram[i].s >> tvprogram[i].e;
        }
        sort(tvprogram,tvprogram+n,cmp);
        int te=-1,cnt=0;
        for(int i=0;i<n;i++){
            if(tvprogram[i].s>=te){
                te=tvprogram[i].e;
                cnt++;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}