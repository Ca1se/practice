#include<iostream>
#include<queue>
using namespace std;

inline long long solve(int num) {
     queue<long long> q;
     q.push(1);
     while(!q.empty()) {
         long long t = q.front();
         q.pop();
         if(!(t % num)) return t;
         q.push(t * 10);
         q.push(t * 10 + 1);
     }
     return 0;
}

int main() {
    ios::sync_with_stdio(false);
    int num;
    while(cin >> num && num) {
        cout << solve(num) << endl;
    }
    return 0;
}