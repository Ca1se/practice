#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct Students
{
    int score;
    string exnumber;
};

bool cmp(Students x, Students y) {
    return x.score == y.score ? x.exnumber<y.exnumber : x.score>y.score;
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w+", stdout);
    ios::sync_with_stdio(false);
    int n, m, g;
    while (cin >> n && n && cin >> m >> g)
    {
        int pmscore[10], cnt = 0;
        Students students[1000];
        for (int i = 0; i < m; i++)
            cin >> pmscore[i];
        for (int i = 0; i < n; i++) {
            int rpn, sum = 0;
            string temps;
            cin >> temps >> rpn;
            for (int j = 0; j < rpn; j++) {
                int temp;
                cin >> temp;
                sum += pmscore[temp-1];
            }
            if (sum >= g) {
                students[cnt].exnumber = temps;
                students[cnt++].score = sum;
            }
        }
        sort(students, students + cnt, cmp);
        cout << cnt << "\n";
        for (int i = 0; i < cnt; i++)  cout << students[i].exnumber << " " << students[i].score << "\n";
    }
    return 0;
}