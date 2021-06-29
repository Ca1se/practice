#include <bits/stdc++.h>
using namespace std;

class Sort {
private:
    int* arr, * ori;
    size_t size;

    void quick_sort_recursion(int l, int r) {
        if(r - l > 1) {
            int i = l, j = r - 1;
            int tmp = arr[i];
            while(i < j) {
                while(i < j && arr[j] > tmp) j--;
                arr[i] = arr[j];
                while(i < j && arr[i] <= tmp) i++;
                arr[j] = arr[i];
            }
            arr[i] = tmp;
            quick_sort_recursion(l, i);
            quick_sort_recursion(i + 1, r);
        }
    }

    inline void sink(int k, int n) {
        while(k * 2 <= n) {
            int j = k * 2;
            if(j + 1 <= n && arr[j] < arr[j + 1]) j++;
            if(arr[k] >= arr[j])    break;
            swap(arr[k], arr[j]);
            k = j;
        }
    }

public:
    Sort(int* arr, size_t size): arr(nullptr), ori(arr), size(size) {
        this->arr = new int[size];
        memcpy(this->arr, arr, size * sizeof(int));
    };

    Sort() = default;

    ~Sort() {
        if(arr) {
            delete[] arr;
            arr = nullptr;
        }
    }

    void create_heap_arr(int* arr, size_t size) {
         this->arr = new int[size + 1];
         memcpy(this->arr + 1, arr, sizeof(int) * size);
    }

    void return_origin() {
        memcpy(arr, ori, size * sizeof(int));
    }

    void select_sort() {
        int minPos, minVal;
        for(size_t i = 0; i < size; i++) {
            minVal = arr[minPos = i];
            for(size_t k = i + 1; k < size; k++) {
                if(arr[k] < minVal) minVal = arr[minPos = k];
            }
            swap(arr[i], arr[minPos]);
        }
    }

    void direct_insert_sort() {
        for(size_t i = 1; i < size; i++) {
            if(arr[i] < arr[i - 1]) {
                int temp = arr[i], k = i - 1;
                for(; k >= 0 && arr[k] > temp; k--) {
                    arr[k + 1] = arr[k];
                }
                arr[k + 1] = temp;
            }
        }
    }

    void bubble_sort() {
        for(size_t i = 0; i < size; i++) {
            for(size_t k = i + 1; k < size; k++) {
                if(arr[i] > arr[k]) swap(arr[i], arr[k]);
            }
        }
    }

    void shell_sort() {
        int h = 1;
        while(h < size / 3) h = 3 * h + 1;
        while(h > 0) {
            for(int i = h; i < size; i++) {
                for(int j = i; j >= h && arr[j] < arr[j - h]; j -= h)
                    swap(arr[j], arr[j - h]);
            }
            h /= 3;
        }
    }

    void quick_sort_recursion() {
        quick_sort_recursion(0, size);
    }

    void heap_sort() {
        int n = size;
        for(int i = n / 2; i >= 1; i--)
            sink(i, n);
        while(n > 1) {
            swap(arr[1], arr[n--]);
            sink(1, n);
        }
    }

    void quick_sort() {
        using pii = pair<int, int>;
        stack<pii> s;
        s.push({0, size});
        while(!s.empty()) {
            pii t = s.top(); s.pop();
            if(t.second - t.first > 1) {
                int i = t.first, j = t.second - 1, tmp = arr[i];
                while(i < j) {
                    while(i < j && arr[j] > tmp) j--;
                    arr[i] = arr[j];
                    while(i < j && arr[i] <= tmp) i++;
                    arr[j] = arr[i];
                }
                arr[i] = tmp;
                s.push({t.first, i});
                s.push({i + 1, t.second});
            }
        }
    }

    void print(int offset = 0) const {
        for(int i = offset; i < (int) size + offset; i++) {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }
};



int main() {
    int arr[] = {23, 34, 534, 234, 65, 34, 20};
    Sort s(arr, sizeof(arr) / sizeof(int));
    cout << "bubble_sort\n";
    s.bubble_sort();
    s.print();

    cout << "direct_insert_sort\n";
    s.return_origin();
    s.direct_insert_sort();
    s.print();

    cout << "quick_sort\n";
    s.return_origin();
    s.quick_sort();
    s.print();

    cout << "quick_sort_recursion\n";
    s.return_origin();
    s.quick_sort_recursion();
    s.print();

    cout << "select_sort\n";
    s.return_origin();
    s.select_sort();
    s.print();

    cout << "shell_sort\n";
    s.return_origin();
    s.shell_sort();
    s.print();

    cout << "heap_sort\n";
    s.create_heap_arr(arr, sizeof(arr) / sizeof(int));
    s.heap_sort();
    s.print(1);
    return 0;
}
