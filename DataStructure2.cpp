#include <bits/stdc++.h>
#define log(msg) cout << msg << "\n"
using namespace std;
const int maxn = 500;

template<typename T>
class List {
private:
    struct Node {
        Node(const T& e): val(e), next(nullptr) {}
        T val;
        Node* next;
    };


    Node* head;

    void sorted_insert(const T& e) {
        Node* t = new Node(e);
        if(head) {
            if(head->val >= e) {
                t->next = head;
                head = t;
                return;
            }
            Node* tar = head;
            while(tar->next != nullptr) {
                if(tar->next->val >= e) {
                    break;
                }
                tar = tar->next;
            }
            t->next = tar->next;
            tar->next = t;
        }else {
            head = t;
        }
    }

public:
    List(): head(nullptr) {}

    void create_list(const T* arr, size_t size) {
        if(size > 0) {
            head = new Node(arr[0]);
            Node* tar = head;
            for(size_t i = 1; i < size; i++) {
                Node* t = new Node(arr[i]);
                tar->next = t;
                tar = t;
            }
        }
    }

    void traverse_list() const {
        Node* tar = head;
        while(tar != nullptr) {
            cout << tar->val << " ";
            tar = tar->next;
        }
        cout << "\n";
    }

    void reserve_list() {
        if(head != nullptr && head->next != nullptr) {
            Node* pre = head, * now = head->next, * t;
            head->next = nullptr;
            while(now != nullptr)  {
                t = now->next;
                now->next = pre;
                pre = now;
                now = t;
            }
            head = pre;
        }
    }

    void delete_even_val_node() {
        Node* now = head, * pre = head;
        while(now != nullptr) {
            if((now->val & 1) == 0) {
                Node* t = now;
                if(now == head) {
                    head = pre = now = now->next;
                }else {
                    pre->next = now->next;
                    now = pre->next;
                }
                delete t;
                continue;
            }
            if(now != pre) {
                pre = now;
            }
            now = now->next;
        }
    }

    void create_sorted_list(const T* arr, size_t size) {
        for(size_t i = 0; i < size; i++) {
            sorted_insert(arr[i]);
        }
    }

    void merge_sorted_list(const List& l) {
        Node* tar = l.head;
        while(tar != nullptr) {
            sorted_insert(tar->val);
            tar = tar->next;
        }
    }
};

void create_random_arr(int* arr, size_t size) {
    for(size_t i = 0; i < size; i++) {
        arr[i] = rand() % 500;
    }
}

int main() {
    int arr[maxn];
    srand(time(nullptr));
    create_random_arr(arr, 10);

    log("1．随机产生或键盘输入一组元素，建立一个带头结点的单向链表（无序）。\n 2. 遍历单向链表");
    List<int> l;
    l.create_list(arr, 10);
    l.traverse_list();

    log("3．把单向链表中元素逆置（不允许申请新的结点空间）。");
    l.reserve_list();
    l.traverse_list();

    log("4．在单向链表中删除所有的偶数元素结点。");
    l.delete_even_val_node();
    l.traverse_list();

    log("5．编写在非递减有序链表中插入一个元素使链表元素仍有序的函数，并利用该函数建立一个非递减有序单向链表。");
    List<int> l1;
    log("原数组:");
    for(size_t i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
    log("有序数组:");
    l1.create_sorted_list(arr, 10);
    l1.traverse_list();

    log("6．利用算法5建立两个非递减有序单向链表，然后合并成一个非递增链表。");
    create_random_arr(arr, 10);
    List<int> l2;
    l2.create_sorted_list(arr, 10);
    log("两有序数组:");
    l1.traverse_list();
    l2.traverse_list();
    l1.merge_sorted_list(l2);
    log("合并后数组:");
    l1.traverse_list();

    return 0;
}
