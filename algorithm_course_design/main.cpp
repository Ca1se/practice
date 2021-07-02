#include <iostream>
#include "graph.h"

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout); // 输入输出重定向到文件

    try {
        Graph g;
        g.CreateGraph();
        int pos = g.ShortestPath();
        if(pos != -1) g.ShowPath((int) pos);
        g.MinJumpNum();
        g.MinimumSpanningTree();
    }catch(const char* errMsg) {
        std::cout << errMsg << "\n";
    };
    return 0;
}
