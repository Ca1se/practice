#include "union_find.h"

int UnionFind::Find(int p) {
    if(list[p] < 0) return p;
    list[p] = Find(list[p]);
    return list[p];
}

void UnionFind::Union(int x, int y) {
    list[x] = y;
}
