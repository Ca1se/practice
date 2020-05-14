#include<iostream>
#include<set>
#include<vector>
using namespace std;
int main(){
    int N;
    while (cin >> N && N)
    {
        ios::sync_with_stdio(false);
        set<vector<int>> hrow;//横行
        set<vector<int>> srow;//竖行
        int sum=0;
        for(int i=0;i<N;i++){
            int point[2];
            vector<int> temp;
            cin >> point[0] >> point[1];
            temp.push_back(point[0]);
            temp.push_back(point[1]);
            srow.insert(temp);
            temp.insert(temp.begin(),point[1]);
            hrow.insert(temp);
        }
        //横竖行计算
        for(auto ith=hrow.begin(), its=srow.begin();ith!=hrow.end();ith++,its++){
            int temp=(*ith++)[1];
            sum+=(*ith)[1]-temp;
            temp=(*its++)[1];
            sum+=(*its)[1]-temp;
        }
        cout << "The length of the fence will be " << sum << " units.\n";
    }
    return 0;
}
