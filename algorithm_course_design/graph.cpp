#include <iostream>
#include <cstddef>
#include <cmath>
#include <stack>
#include "graph.h"
#include "min_priority_queue.h"

//从文件读取数据构造图
void Graph::CreateGraph() {
    int n, d, x, y;
    std::cin >> n >> d;

    points.push_back(std::make_pair(0, 0));

    // 输入鳄鱼所在的点
    for(int i = 0; i < n; i++) {
        std::cin >> x >> y;
        int pos = points.size();
        points.push_back(std::make_pair(x, y));
        const auto& p = points.back();

        // 输入的点与现有的点构成的边
        for(size_t k = 1; k < points.size() - 1; k++) {
            const auto& it = points[k];
            if(abs(it.first) == 50 || abs(it.second) == 50) continue;
            double dist = sqrt((p.first - it.first) * (p.first - it.first) + (p.second - it.second) * (p.second - it.second));
            if(dist <= d) {
                edges[pos].push_back(std::make_pair(k, dist));
                edges[k].push_back(std::make_pair(pos, dist));
            }
        }

        double dist = sqrt(p.first * p.first + p.second * p.second) - 7.5;
        if(dist <= d) {
            edges[0].push_back(std::make_pair(pos, dist));
            edges[pos].push_back(std::make_pair(0, dist));
        }
        
        auto insert_edge = [&](double py1, int px2, int py2) {
            edges[pos].push_back(std::make_pair(points.size(), py1));
            points.push_back(std::make_pair(px2, py2));
        };
        
        // 检查此点是否有上拓展点, 下同, 为 右 下 左 拓展点
        if(50 - y <= d) insert_edge(50 - y, x, 50);
        if(50 - x <= d) insert_edge(50 - x, 50, y);
        if(y + 50 <= d) insert_edge(y + 50, x, -50);
        if(x + 50 <= d) insert_edge(x + 50, -50, y);
    }
}

std::pair<double, size_t> Graph::ShortestPath() {
    memset(path, -1, sizeof path);
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < MAX_POINT_NUM; i++) dist[i] = INF;
    dist[0] = 0;

    using pdi = std::pair<double, int>;
    MinPriorityQueue<pdi> q;
    q.push(std::make_pair(0, 0));

    while(!q.empty()) {
        pdi t = q.top(); q.pop();
        if(vis[t.second])   continue;
        vis[t.second] = true;

        for(size_t i = 0; i < edges[t.second].size(); i++) {
            const auto& it = edges[t.second][i];
            if(dist[it.first] > dist[t.second] + it.second) {
                dist[it.first] = dist[t.second] + it.second;
                path[it.first] = t.second;
                q.push(std::make_pair(dist[it.first], it.first));
            }
        }
    }

    double minn = INF;
    size_t minPos;
    //sort
    for(size_t i = 0; i < points.size(); i++) {
        if((abs(points[i].first) == 50 || abs(points[i].second) == 50) && dist[i] < minn)
            minn = dist[i], minPos = i;
    }

    return (minn != INF ? std::make_pair(minn, minPos) : std::make_pair(-1.0, (size_t) 0));
}

void Graph::ShowPath(int pos) const {
    std::stack<size_t> s;
    while(pos >= 0) {
        s.push(pos);
        pos = path[pos];
    }
    while(!s.empty()) {
        std::cout << "(" << points[s.top()].first << ", " << points[s.top()].second << ")\n";
        s.pop();
    }
}
