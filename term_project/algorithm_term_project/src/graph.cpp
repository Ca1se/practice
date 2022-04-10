#include <iostream>
#include <cstddef>
#include <cmath>
#include <stack>
#include <set>
#include "graph.h"
#include "bfs.h"
#include "min_priority_queue.h"
#include "quick_sort.h"
#include "union_find.h"

Graph::Graph()
: _points(), _edges(MAX_POINT_NUM), _borderPoint(), _pointDist(), _unionEdges() {}

Graph::Edge::Edge(int u, int v, int w): u(u), v(v), w(w) {}

bool Graph::Edge::operator>= (const Edge& rhs) const {
    return this->w >= rhs.w;
}

bool Graph::Edge::operator<= (const Edge& rhs) const {
    return this->w <= rhs.w;
}

void Graph::PrintPoint(int pos) const {
    std::cout << "(" << _points[pos].first << ", " << _points[pos].second << ")\n";
}

//从文件读取数据构造图
void Graph::CreateGraph() {
    int n, d, x, y;
    std::cin >> n >> d;

    _points.push_back(std::make_pair(0, 0));

    // 输入鳄鱼所在的点
    for(int i = 0; i < n; i++) {
        std::cin >> x >> y;
        int pos = _points.size();
        _points.push_back(std::make_pair(x, y));

        // 输入的点与现有的点构成的边
        for(size_t k = 1; k < _points.size() - 1; k++) {
            const auto& it = _points[k];
            if(abs(it.first) == 50 || abs(it.second) == 50) continue;
            double dist = sqrt((x - it.first) * (x - it.first) + (y - it.second) * (y - it.second));
            if(dist <= d) {
                _edges[pos].push_back(std::make_pair(k, dist));
                _edges[k].push_back(std::make_pair(pos, dist));

                _unionEdges.push_back(Edge(pos, k, dist));
            }
        }

        double dist = sqrt(x * x + y * y) - 7.5;
        if(dist < 0 || x >= 50 || y >= 50) {
            throw "invalid data";
        }
        _pointDist.push_back(std::make_pair(dist, pos));
        if(dist <= d) {
            _edges[0].push_back(std::make_pair(pos, dist));
            _edges[pos].push_back(std::make_pair(0, dist));

            _unionEdges.push_back(Edge(0, pos, dist));
        }
        
        auto insert_edge = [&](double py1, int px2, int py2) {
            _edges[pos].push_back(std::make_pair(_points.size(), py1));
            _borderPoint.push_back(_points.size());
            _points.push_back(std::make_pair(px2, py2));
        };
        
        // 检查此点是否有上拓展点, 下同, 为 右 下 左 拓展点
        if(50 - y <= d) insert_edge(50 - y, x, 50);
        if(50 - x <= d) insert_edge(50 - x, 50, y);
        if(y + 50 <= d) insert_edge(y + 50, x, -50);
        if(x + 50 <= d) insert_edge(x + 50, -50, y);
    }
}

size_t Graph::ShortestPath() {
    memset(_path, -1, sizeof _path);
    memset(_vis, 0, sizeof _vis);
    for(int i = 0; i < MAX_POINT_NUM; i++) _dist[i] = INF;
    _dist[0] = 0;

    using pdi = std::pair<double, int>;
    MinPriorityQueue<pdi> q;
    q.push(std::make_pair(0, 0));

    while(!q.empty()) {
        pdi t = q.top(); q.pop();
        if(_vis[t.second])   continue;
        _vis[t.second] = true;

        for(size_t i = 0; i < _edges[t.second].size(); i++) {
            const auto& it = _edges[t.second][i];
            if(_dist[it.first] > _dist[t.second] + it.second) {
                _dist[it.first] = _dist[t.second] + it.second;
                _path[it.first] = t.second;
                q.push(std::make_pair(_dist[it.first], it.first));
            }
        }
    }

    double minn = INF;
    size_t minPos;
    //sort
    for(size_t i = 0; i < _borderPoint.size(); i++) {
        if(_dist[_borderPoint[i]] < minn) {
            minn = _dist[_borderPoint[i]];
            minPos = _borderPoint[i];
        }
    } 

    std::cout << minn << "\n";

    return minn != INF ? minPos : -1;
}

void Graph::ShowPath(int pos) const {
    std::stack<size_t> s;
    while(pos > 0) {
        s.push(pos);
        pos = _path[pos];
    }
    while(!s.empty()) {
        PrintPoint(s.top());
        s.pop();
    }
    std::cout << "\n";
}

void Graph::MinJumpNum() const {
    BFS b;    
    b.bfs(0, _points, _edges);
    std::cout << "\n";
}

void Graph::MinimumSpanningTree() {
    UnionFind u(MAX_POINT_NUM);
    std::set<int> s;
    int ans = 0;

    quicksort(_unionEdges, 0, _unionEdges.size() - 1);
    for(size_t i = 0; i < _unionEdges.size(); i++) {
        const auto& it = _unionEdges[i];
        int p = u.Find(it.u), q = u.Find(it.v);
        if(p != q) {
            ans += it.w;
            s.insert(it.u);
            s.insert(it.v);
            u.Union(p, q);
        }
    }
    
    std::cout << ans << "\n";
    for(auto it: s) {
        PrintPoint(it);
    }
    std::cout << "\n";
}
