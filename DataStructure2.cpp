#include <bits/stdc++.h>
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

    void reserve_list() const {
        if(head != nullptr && head->next != nullptr) {
            Node* pre = head->next, * now = head->next, * t;
            while(now != nullptr)  {
                t = now->next;
                if(pre != now) {
                    now->next = pre;
                }
                pre = now;
                now = t;
            }
        }
    }
};

int main() {
    int n, arr[maxn];
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    return 0;
}
