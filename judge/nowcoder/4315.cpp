#include <cstdio>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

const int maxn = 200 + 5;

unordered_map<int, int> index;
int n, k;
int tmp, tmp1;
int name[maxn];
int happy[maxn];


int main() {
    scanf("%d %d %s", &n, &k, (char*) &tmp);
    index[tmp] = 0;
    name[0] = tmp;
    for(int i = 1; i < n; i++) {
        scanf("%s %d", (char*) &tmp, happy + i);
        index[tmp] = i;
        name[i] = tmp;
    }
    for(int i = 0; i < k; i++) {
        scanf("%s %s %d", (char*) &tmp, (char*) &tmp1, );
    }
    return 0;
}
