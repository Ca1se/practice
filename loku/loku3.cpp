#include<iostream>
#include<string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    int n, pprelength = 0, prelength = 0, nowlength = 0, max = -1;
    string st;
    cin >> n >> st;
    for (int i = 0; i < n; i += nowlength) {
        int j;
        for (j = i + 1; j < n && st[j] != st[j - 1]; j++);
        nowlength = j - i;
        max = (pprelength + prelength + nowlength) > max ? (pprelength + prelength + nowlength) : max;
        pprelength = prelength;
        prelength = nowlength;
    }
    cout << max << endl;
    return 0;
}