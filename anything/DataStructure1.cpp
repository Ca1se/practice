#include <bits/stdc++.h>
#define MAXSIZE 100
using namespace std;
class SeqList {
private:
    using ElemType = int;
    typedef struct list {
        ElemType elem[MAXSIZE];
        int length;
    }SqList;

    list *pL;

public:
    SeqList(): pL(new SqList) {}
    ~SeqList() {
        if(pL != nullptr) {
            delete pL;
            pL = nullptr;
        }
    }
    //输入一组整型元素序列，建立顺序表
    void create_list() {
        size_t len;
        cout << "Please input length of the sequence list:" << endl;
        cin >> len;
        if(len > MAXSIZE)    throw "list length is too long";
        cout << "Please input elements of the sequence list:" << endl;
        for(size_t i = 0; i < len; i++) {
            cin >> pL->elem[i];
        }
        pL->length = len;
    }
    //实现该顺序表的遍历
    void traversal_list() const {
        cout << "All elements in list:" << endl;
        for(size_t i = 0; i < pL->length; i++) {
            cout << pL->elem[i] << " ";
        } 
        cout << endl;
    }
    //在该顺序表中进行顺序查找某一元素,查找成功返回1,否则返回0
    int find_element(int e) const {
        for(size_t i = 0; i < pL->length; i++) {
            if(pL->elem[i] == e)    return 1;
        }
        return 0;
    }
    //判断该顺序表中元素是否对称,对称返回1,否则返回0
    int is_list_symmetry() const {
        int i = 0, j = pL->length - 1;
        while(i < j) {
            if(pL->elem[i++] != pL->elem[j--])  return 0;
        }
        return 1;
    }
    //实现把该表中所有奇数排在偶数之前,即表的前面为奇数,后面为偶数
    void arrange() {
        int i = 0, j = pL->length - 1;
        while(i < j) {
            while(i < j && (pL->elem[i] & 1))   i++;
            while(i < j && !(pL->elem[j] & 1))  j--;
            swap(pL->elem[i], pL->elem[j]);
        }
    }
    //输入整型元素序列利用有序表插入算法建立一个有序表
    void create_sorted_list() {
        size_t len;
        int t;
        pL->length = 0;
        cout << "Please input length of sequence list:" << endl;
        cin >> len;
        cout << "Please input elements of sequence list:" << endl;
        while(len--) {
            cin >> t;
            insert(t);
        }
    }

private:
    void insert(int e) {
        if(pL->length == MAXSIZE)   throw "list is full";
        pL->length++;
        for(size_t i = 0; i < pL->length - 1; i++) {
            if(pL->elem[i] > e) {
                for(size_t j = pL->length - 1; j > i; j--) {
                    pL->elem[j] = pL->elem[j - 1];
                }
                pL->elem[i] = e;
                return;
            }
        }
        pL->elem[pL->length - 1] = e;
    }
public:
    //利用算法6建立两个非递减有序表并把它们合并成一个非递减有序表
    void insert_merge(const SeqList& s) {
        if(pL->length + s.pL->length > MAXSIZE) throw "The length of target list is too long";
        for(size_t i = 0; i < s.pL->length; i++) {
            insert(s.pL->elem[i]);
        }
    }
};
int main() {
    SeqList s;
    try {
        cout << "algorithm 1 test:" << endl;
        //input 32 435 123 543 23 65 123 64
        s.create_list();

        cout << "algorithm 2 test:" << endl;
        s.traversal_list();

        cout << "algorithm 3 test:" << endl;
        cout << s.find_element(23) << endl; // 1
        cout << s.find_element(62) << endl; // 0

        cout << "algorithm 4 test:" << endl;
        cout << s.is_list_symmetry() << endl; // 0
        //input 1 2 3 4 5 4 3 2 1
        s.create_list();
        cout << s.is_list_symmetry() << endl; // 1

        cout << "algorithm 5 test" << endl;
        s.arrange();
        s.traversal_list();

        cout << "algorithm 6 test" << endl;
        SeqList ts;
        ts.create_sorted_list();
        ts.traversal_list();

        cout << "algorithm 7 test" << endl;
        s.create_sorted_list();
        s.insert_merge(ts);
        s.traversal_list();

    }catch(const char* errmsg) {
        cerr << errmsg << endl;
    }
    return 0;
}
