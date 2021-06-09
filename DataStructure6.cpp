#include <bits/stdc++.h>
using namespace std;
class HashList {
private:
    static const int mapLength = 15;
    static const int BASE = 15;
    size_t size; 
    int* list;
    bool hasVal[mapLength];
public:
    HashList(): size(0), list(nullptr), hasVal() {
        list = new int[mapLength];
    }

    ~HashList() {
        if(list) {
            delete[] list;
            list = nullptr;
        }
    }

    void insert(int key) {
        if(size == mapLength)   throw "map is full";
        int p = key % BASE;
        while (hasVal[p])    p = (p + 1) % BASE;
        list[p] = key;
        hasVal[p] = true;
        size++;
    }

    bool find(int key) const {
        int p = key % BASE;
        for(int i = 0; i < mapLength - 1; i++, p = (p + 1) % mapLength) {
            if(!hasVal[p]) {
                return false;
            }else if(list[p] == key) {
                return true;
            }
        }
        return false;
    }

};
int main() {
    int t;
    HashList list;
    cout << "Please input 10 numbers:" << endl;
    for(int i = 0; i < 10; i++) {
        cin >> t;
        list.insert(t);
    }
    char choose; 
    while(1) {
        cout << "Do you want to find a number in hashlist?" << endl;
        do {
            cin >> choose;
        }while(choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
        if(choose == 'y' || choose == 'Y') {
            int key;
            cout << "Please input the number:";
            cin >> key;
            cout << (list.find(key) ? "found it" : "cant found it") << endl;
        }else {
            break;
        }
    }
    return 0;
}
