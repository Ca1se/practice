/* UVa 122 树的层次遍历*/
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
struct Node {
    bool have_value;
    int value;
    Node* left, * right;
    Node() :have_value(false), left(NULL), right(NULL) {};
};

Node* root = new Node();
vector<Node*> q;
bool CanPrint() {
    Node* target = root;
    queue<Node*> temp;
    temp.push(target);
    while (!temp.empty())
    {
        Node* t = temp.front();
        q.push_back(t);
        temp.pop();
        if (!t->have_value)  return false;
        if (t->left != NULL)   temp.push(t->left);
        if (t->right != NULL)  temp.push(t->right);
    }
    return true;
}

void Print_Ans() {
    if (CanPrint()) {
        for (auto i = q.begin(); i != q.end(); i++) {
            if (i != q.begin())    cout << " ";
            cout << (*i)->value;
        }
        cout << endl;
        q.clear();
    }
    else {
        cout << "not complete" << endl;
        q.clear();
    }
}

int main() {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w+", stdout);
    ios::sync_with_stdio(false);
    char a[500];
    bool judge = true;
    while(cin >> a)
    {
        Node* target = root;
        if (a[1] == ')') {
            if (judge) {
                Print_Ans();
            }
            else {
                cout << "not complete" << endl;
                judge = true;
            }
            root = new Node();
            continue;
        }
        char str[20];
        strcpy(str, strchr(a, ',') + 1);
        for (int i = 0; i < strlen(str)-1; i++) {
            if (str[i]=='L') {
                if (!target->left)   target->left = new Node();
                target = target->left;
            }else if(str[i]=='R')
            {
                if (!target->right)   target->right = new Node();
                target = target->right;
            }
        }
        if(!target->have_value){
            sscanf(a + 1, "%d", &target->value);
            target->have_value = true;
        }else{
            judge=false;
        }
    }
    return 0;
}