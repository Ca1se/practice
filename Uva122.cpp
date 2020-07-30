#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
struct Tree
{
    int value;
    string road;
};

bool cmp(Tree x, Tree y){
    return x.road.size() == y.road.size() ? x.road < y.road : x.road.size() < y.road.size();
}

bool cmp1(string x, string y){
    return x.size() == y.size() ? x < y : x.size() < y.size();
}

int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    Tree* node = new Tree[256];
    string* mark = new string[256];
    string tmp;
    int i = 0;
    bool judge = true;
    while (cin >> tmp)
    {
        if (tmp == "()")
        {
            if(judge){
                sort(node, node + i, cmp);
                sort(mark, mark + i, cmp1);
                for (int j = 0; j < i; j++){
                    if (find(mark, mark + j + 1, node[j].road.substr(0,node[j].road.size() ? node[j].road.size() - 1 : 0)) == mark + j + 1){
                        judge = false;
                        break;
                    }
                }
            }
            if (judge){
                for (int j = 0; j < i; j++){
                    int a = node[j].value;
                    cout << node[j].value;
                    if (j != i - 1) cout << " ";
                }
            }
            else{
                cout << "not complete";
            }
            i = 0;
            judge = true;
            cout << endl;
            continue;
        }
        if(judge){
            if(find(mark, mark + i, string(&tmp[tmp.find(",")+1], &tmp[tmp.find(")")])) != mark + i){
                judge = false;
                continue;
            }
            node[i].value = atoi(string(&tmp[tmp.find("(")+1], &tmp[tmp.find(",")]).c_str());
            node[i].road = mark[i] = string(&tmp[tmp.find(",")+1], &tmp[tmp.find(")")]);
            i++;
        }
    }
    delete[] node;
    delete[] mark;
    return 0;
}