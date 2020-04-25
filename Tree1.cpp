//兄弟儿子二叉树的创建,查找,最大高度,前中后序遍历
#include<iostream>
#include<cstdlib>
using namespace std;
struct Tree {
    Tree* NextChildNode;
    Tree* NextBraNode;
    char NodeName[11];
};
struct Queue {
    Tree* TreeData;
    Queue* next;
};
Queue* head, * tail;
//---------队列操作---------
//void initqueue(Queue* queue);
void enqueue(Tree*& Node);
void dequeue(Tree*& getnode);
//void isaqueueempty(Queue* queue);
//---------树操作----------
//void inittree(Tree* &tree);
void treeheight(Tree* tree);
void pre_travel(Tree* tree);
void mid_travel(Tree* tree);
void past_travel(Tree* tree);
//--------------------------------------------------------------
void enqueue(Tree*& node) {
    Queue* temp = (Queue*)malloc(sizeof(Queue));
    if (temp == NULL)  return;
    temp->TreeData = node;
    temp->next = NULL;
    if (head == NULL)
        head = temp;
    else
        tail->next = temp;
    tail = temp;
}
void dequeue(Tree*& getnode) {
    if (head == NULL)  return;
    getnode = head->TreeData;
    Queue* temp = head;
    head = head->next;
    free(temp);
}
void inittree(Tree* &tree) {
    tree = (Tree*)malloc(sizeof(Tree));
    cout << "输入根节点: ";
    cin >> tree->NodeName;
    tree->NextBraNode = NULL;
    enqueue(tree);
    while (head != NULL)
    {
        Tree* tempnode;
        dequeue(tempnode);
        cout << "输入节点" << tempnode->NodeName << "的左子节点(输入\"#\"表示无子节点): ";
        Tree* cnode = (Tree*)malloc(sizeof(Tree));
        cin >> cnode->NodeName;
        if ((cnode->NodeName)[0] == '#') {
            tempnode->NextChildNode = NULL;
            free(cnode);
            continue;
        }
        else {
            tempnode->NextChildNode = cnode;
            enqueue(cnode);
        }
        cout << "输入节点" << tempnode->NodeName << "的右子节点(输入\"#\"表示无右子节点): ";
        Tree* bnode = (Tree*)malloc(sizeof(Tree));
        cin >> bnode->NodeName;
        if ((bnode->NodeName)[0] == '#') {
            tempnode->NextChildNode->NextBraNode = NULL;
            free(bnode);
        }
        else {
            tempnode->NextChildNode->NextBraNode = bnode;
            tempnode->NextChildNode->NextBraNode->NextBraNode = NULL;
            enqueue(bnode);
        }
    }
}
void pre_tarvel(Tree* &tree) {
    Tree* p = tree;
    do {
        cout << p->NodeName;
        if (p->NextChildNode != NULL) {
            pre_tarvel(p->NextChildNode);
        }
        p = p->NextBraNode;
    } while (p != NULL);
}
int main() {
    Tree* atree;
    inittree(atree);
    pre_tarvel(atree);
}