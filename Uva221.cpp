#include<bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;

struct Building {
    int id;
    double x, y, w, d, h;
    bool operator< (const Building& rhs) const {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
}b[maxn];

double x[maxn * 2];
int n;

bool cover(int i, double mx) {
    return b[i].x <= mx && b[i].x + b[i].w >= mx;
}

bool visiable(int i, double mx) {
    if(!cover(i, mx))   return false;
    for(int j = 0; j < n; j++){
        if(b[j].y < b[i].y && b[j].h >= b[i].h && cover(j, mx)) return false;
    }
    return true;
}

int main() {
    int test = 0;
    while(cin >> n && n){
        for(int i = 0; i < n; i++){
            cin >> b[i].x >> b[i].y >> b[i].w >> b[i].d >> b[i].h;
            x[i * 2] = b[i].x; x[i * 2 + 1] = b[i].x + b[i].w;
            b[i].id = i + 1;
        }
        sort(b, b + n);
        sort(x, x + 2 * n);
        int m = unique(x, x + 2 * n) - x;
        if(test++)  cout << '\n';
        cout << "For map #" << test << ", the visible buildings are numbered as follows:\n" << b[0].id;
        for(int i = 1; i < n; i++){
            bool judge = false;
            for(int j = 0; j < m - 1; j++){
                if(visiable(i, (x[j] + x[j + 1]) / 2)){
                    judge = true;
                    break;
                }
            }   
            if(judge)   cout << ' ' << b[i].id;
        }
        cout << '\n';
    }
    return 0;
}