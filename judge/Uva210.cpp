#include<iostream>
#include<deque>
#include<vector>
#include<string>
#include<map>
using namespace std;
struct Program{
    int step = 0;
    int num;
    vector<string> statement;
};

int main(){
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdout);
    int testtimes;
    cin >> testtimes;
    for(int i = 0; i < testtimes; i++){
        int n, t1, t2, t3, t4, t5, q, timecount = 0;
        bool islocked = false;
        deque<Program> waitqueue, forbidqueue;
        map<char,int> var;
        Program program;
        string tmp;
        cin >> n >> t1 >> t2 >> t3 >> t4 >> t5 >> q;
        getchar();
        for(int j = 0; j < n && getline(cin, tmp);){
            program.statement.push_back(tmp);
            if(tmp == "end"){
                program.num = j + 1;
                waitqueue.push_back(program);
                program.statement.clear();
                j++;
            }
        }
        while (!waitqueue.empty()){
            Program temp = waitqueue.front();
            bool puttoback = true;
            waitqueue.pop_front();
            for(temp.step; timecount < q; temp.step++){
                string sta = temp.statement[temp.step];
                if(sta[2] == '='){// v = 1
                    var[sta[0]] = atoi(string(sta, 4).c_str());
                    timecount += t1;
                }else if(sta[2] == 'i'){// print v
                    cout << temp.num << ": " << var[sta[6]] << endl;
                    timecount += t2;
                }else if(sta[2] == 'c'){// lock
                    if(islocked){
                        forbidqueue.push_back(temp);
                        puttoback = false;
                        break;
                    }
                    islocked = true;
                    timecount += t3;
                }else if(sta[2] == 'l'){// unlock
                    islocked = false;
                    if(!forbidqueue.empty()){
                        waitqueue.push_front(forbidqueue.front());
                        forbidqueue.pop_front();
                    }
                    timecount += t4;
                }else{// end
                    puttoback = false;
                    break;
                }
            }
            if(puttoback){
                waitqueue.push_back(temp);
            }
            timecount = 0;
        }
        if(i != testtimes - 1){
            cout << endl;
        }
    }
    return 0;
}