#include <bits/stdc++.h>
using namespace std;
class BinTree {
private:
    struct Node {
        Node(): val(), lchild(nullptr), rchild(nullptr) {}
        char val;
        Node* lchild, *rchild;
    };

    Node* root;
    size_t pos;
public:
    explicit BinTree(const string& str): root(nullptr), pos(0) {
        create_tree(&root, str);
    }

    void mid_travel_tree_recursion() const {
        mid_travel_tree_recursion(root);
        cout << endl;
    }

    void mid_travel_tree() const {
        stack<Node*> s;
        Node* target = root;
        while(target != nullptr || !s.empty()) {
            while(target != nullptr) {
                s.push(target);
                target = target->lchild;
            }
            if(!s.empty()) {
                target = s.top();
                cout << target->val;
                s.pop();
                target = target->rchild;
            }
        }
        cout << endl;
    }

    int tree_height() const {
        return tree_height(root, 1);
    }

    int tree_leaves() const {
        int num = 0;
        tree_leaves(root, num);
        return num;
    }

private:

    int tree_height(Node* r, int height) const {
        if(r->lchild == nullptr && r->rchild == nullptr) {
            return height;
        }else {
            int maxHeight = 0;
            if(r->lchild)   maxHeight = tree_height(r->lchild, height + 1);
            if(r->rchild)   maxHeight = max(tree_height(r->rchild, height + 1), maxHeight);
            return maxHeight;
        }
    }

    void tree_leaves(Node* r, int& num) const {
        if(r->lchild == nullptr && r->rchild == nullptr) {
            num++;
        }else {
            if(r->lchild)   tree_leaves(r->lchild, num);
            if(r->rchild)   tree_leaves(r->rchild, num);
        }
    }

    void create_tree(Node** r, const string& str) {
        if(pos < str.size() && str[pos++] != '#') {
            *r = new Node;
            (*r)->val = str[pos - 1];
            create_tree(&((*r)->lchild), str);
            create_tree(&((*r)->rchild), str);
        }
    }

    void mid_travel_tree_recursion(Node* r) const {
        if(r != nullptr) {
            mid_travel_tree_recursion(r->lchild);
            cout << r->val;
            mid_travel_tree_recursion(r->rchild);
        }
    }
};
int main() {
    string s = "AB##C#EF##G##";
    BinTree tree(s);
    tree.mid_travel_tree();
    tree.mid_travel_tree_recursion();
    cout << tree.tree_height() << endl;
    cout << tree.tree_leaves() << endl;

    return 0;
}
