#ifndef _BFS_H_
#define _BFS_H_

#include <cstring>
#include "queue.h"
#include "vector.h"

class BFS {
private:
    static const int MAX_POINT_NUM = 100 * 5;

    struct Tuple {
        Tuple(int pos, int num);
        Tuple() = default;
        int pos;
        int jumpNum;
        Vector<int> path;
    };

    int d[MAX_POINT_NUM];
    bool visit[MAX_POINT_NUM];

public:
    void bfs(int t, const Vector<std::pair<int, int>>& points, const Vector<Vector<std::pair<int, double>>>& edges);
};

#endif
