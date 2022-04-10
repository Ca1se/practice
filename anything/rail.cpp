#include<bits/stdc++.h>
using namespace std;

int main() {
     freopen("test.in", "r", stdin);
     freopen("test.out", "w", stdout);
     ios::sync_with_stdio(false);
     int n, i, squ[1005];
     while(cin >> n && n) {
          while(cin >> squ[0] && squ[0]) {
               stack<int> s;
               i = 1; bool judge = true;
               for(int j = 1; j < n; j++)    cin >> squ[j];
               for(int j = 0; j < n;) {
                    if(i == squ[j]) {
                         i++;
                         j++;
                    }else if(!s.empty() && s.top() == squ[j]) {
                         s.pop();
                         j++;
                    }else {
                         s.push(i);
                         i++;
                    }
                    if(i > n + 1) {
                         judge = false;
                         break;
                    }
               }
               if(judge) {
                    cout << "Yes\n";
               }else{
                    cout << "No\n";
               }
          }
          cout << '\n';
     }
     return 0;
}