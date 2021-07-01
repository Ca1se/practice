#include<bits/stdc++.h>
#include"min_priority_queue.h"
using namespace std;

int main() {
    MinPriorityQueue<int> q;
    srand(time(nullptr));
    
    
    while(!q.empty()) {
        cout << q.top() << endl;
        q.pop();
    }
    return 0;
}
