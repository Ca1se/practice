#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "vector.h"

class Graph {
    using pii = std::pair<int, int>;
    using pid = std::pair<int, double>;
    static const int MAX_POINT_NUM = 100 * 5;
    static const int INF = 0x3f3f3f3f;
private:
    Vector<pii> points;
    Vector<pid> edges[MAX_POINT_NUM];
    bool vis[MAX_POINT_NUM];
    double dist[MAX_POINT_NUM];
    int path[MAX_POINT_NUM];

public:
    void CreateGraph();
    std::pair<double, size_t> ShortestPath();
    void ShowPath(int pos) const;
};

#endif
