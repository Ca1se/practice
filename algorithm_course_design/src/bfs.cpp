#include <iostream>
#include "bfs.h"

void BFS::bfs(int t, const my::vector<std::pair<int, int>>& points, const my::vector<my::vector<std::pair<int, double>>>& edges)
{
    memset(d, 0, sizeof d);
    memset(visit, 0, sizeof visit);

    Queue<Tuple> q;
    q.push(Tuple(t, 0));

    while(!q.empty())
    {
        Tuple& t = q.front_data();
        if(abs(points[t.pos].first) == 50 || abs(points[t.pos].second) == 50) {
            std::cout << t.jumpNum << "\n";
            //print
            for(int i = 0; i < (int) t.path.size(); i++) {
                int p = t.path[i];
                std::cout << "(" << points[p].first << ", " << points[p].second << ")\n";
            }
            return;
        }

        if(!visit[t.pos]) {
            visit[t.pos] = true;
            t.jumpNum++;
            const my::vector<std::pair<int, double>> &it = edges[t.pos];
            for (int i = 0; i < (int) it.size(); i++) {
                t.pos = it[i].first;
                t.path.push_back(it[i].first);
                q.push(t);
                t.path.pop_back();
            }
        }
        q.pop();
    }
    std::cout << "-1\n";
}

BFS::Tuple::Tuple(int pos, int num): pos(pos), jumpNum(num) {}
