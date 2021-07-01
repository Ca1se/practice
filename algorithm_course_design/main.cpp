#include <iostream>
#include "graph.h"

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout); // 输入输出重定向到文件

    Graph g;
    g.CreateGraph();
    auto [ans, pos] = g.ShortestPath();
    std::cout << ans << "\n";
    if(ans != -1) g.ShowPath((int) pos);
    return 0;
}
