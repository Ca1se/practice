#include<iostream>
#include<string>
#include<queue>
using namespace std;
struct Tree
{
    string value;
    Tree* Lnext = NULL;
    Tree* Rnext = NULL;
};

queue<Tree*> tree;

void removetree(){
    while (!tree.empty())
    {
        Tree* tmp = tree.front();
        tree.pop();
        delete tmp;
    }
}

int main(){
    //freopen("test.in","r",stdin);
    //freopen("test.out","w+",stdout);
    string tmp;
    Tree* root = new Tree;
    bool judge = true;
    tree.push(root);
    while (cin >> tmp)
    {
        if(tmp == "()"){
            if(judge){
                queue<Tree*> q;
                q.push(root);
                while (!q.empty())
                {
                    Tree* p = q.front();
                    q.pop();
                    if(!p->value.size()){
                        judge = false;
                        break;
                    }
                    if(p->Lnext != NULL){
                        q.push(p->Lnext);
                    }
                    if(p->Rnext != NULL){
                        q.push(p->Rnext);
                    }
                }
            }
            if(judge){
                queue<Tree*> q;
                q.push(root);
                while (!q.empty())
                {
                    Tree* p = q.front();
                    q.pop();
                    cout << p->value;
                    if(p->Lnext != NULL){
                        q.push(p->Lnext);
                    }
                    if(p->Rnext != NULL){
                        q.push(p->Rnext);
                    }
                    if(q.size()){
                        cout << " ";
                    }
                }
            }else{
                cout << "not complete";
            }
            cout << endl;
            removetree();
            root = new Tree;
            judge = true;
            continue;
        }
        if(judge){
            string step = string(&tmp[tmp.find(",")+1]);
            string val = string(&tmp[1],&tmp[tmp.find(",")]);
            Tree* target = root;
            for(int i = 0; i < step.size(); i++){
                if(step[i] == 'L'){
                    if(target->Lnext == NULL){
                        Tree* node = new Tree;
                        target->Lnext = node;
                        target = node;
                        tree.push(target);
                    }else{
                        target = target->Lnext;
                    }
                }else if(step[i] == 'R'){
                    if(target->Rnext == NULL){
                        Tree* node = new Tree;
                        target->Rnext = node;
                        target = node;
                        tree.push(target);
                    }else{
                        target = target->Rnext;
                    }
                }else{
                    if(!target->value.size()){
                        target->value = val;
                    }else{
                        judge = false;
                    }
                }
            }
        }
    }
    delete root;
    return 0;
}