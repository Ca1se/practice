#include <bits/stdc++.h>
using namespace std;

int quick_divide(int* arr, size_t len) {
    int l = 0, r = len;
    int i = l, j = r - 1;
    while(l < r) {
        int tmp = arr[i];
        while(i < j) {
            if(i < j && arr[j] >= tmp)   j--;
            arr[i] = arr[j];
            if(i < j && arr[i] < tmp)  i++;
            arr[j] = arr[i];
        }
        arr[i] = tmp;
        if(i == len / 2) {
            break;
        }else if(i < len / 2) {
            l = ++i;
            j = r - 1;
        }else {
            r = j--;
            i = l;
        }
    }
    int lsum = 0, rsum = 0;
    for(int r = 0; r < len / 2; r++) {
        lsum += arr[r];
    }
    for(int r = len / 2; r < len; r++) {
        rsum += arr[r];
    }
    return rsum - lsum;
}

int main() {
    int arr[] = {2, 2, 2, 1, 1};
    cout << quick_divide(arr, sizeof(arr) / sizeof(int)) << endl;
    return 0;
}
