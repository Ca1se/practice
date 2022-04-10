#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_

#include <cstring>

class UnionFind {
private:
    int* list;
public:
    UnionFind(size_t length): list(nullptr) {
        list = new int[length];
        memset(list, -1, sizeof(int) * length);
    }

    int Find(int p);
    void Union(int x, int y);
};

#endif
