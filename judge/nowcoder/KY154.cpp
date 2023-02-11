// https://www.nowcoder.com/practice/f7c80167c5b04fd2ac4b6d7080a73f01?tpId=63&tqId=29601&tPage=2&rp=2&ru=/ta/zju-kaoyan

#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

static constexpr int maxn = 1000 + 5;
static constexpr int maxm = 10 + 5;
int n, m, g;
int tscore[maxm];
int gscore[maxn];
std::map<std::string, int> nti;
std::map<int, std::string> itn;
std::vector<int> good;

int main() {
    char buf[64];
    int tn, ti;
    while (std::scanf("%d%d%d", &n, &m, &g) != EOF && n != 0) {
        nti.clear();
        itn.clear();
        good.clear();
        for(int i = 1; i <= m; i++)
            std::scanf("%d", tscore + i);
        for(int i = 0; i < n; i++) {
            std::scanf("%s", buf);
            nti.insert(std::pair<std::string, int>(std::string(buf), i));
            itn.insert(std::pair<int, std::string>(i, std::string(buf)));
            scanf("%d", &tn);
            gscore[i] = 0;
            for(int j = 0; j < tn; j++) {
                scanf("%d", &ti);
                gscore[i] += tscore[ti];
            }
            if(gscore[i] >= g)
                good.push_back(i);
        }
        std::sort(good.begin(), good.end(), [](int a, int b) {
            return gscore[a] == gscore[b] ? itn[a] < itn[b] : gscore[a] > gscore[b];
        });
        std::printf("%zu\n", good.size());
        for(int i: good) {
            std::printf("%s %d\n", itn[i].c_str(), gscore[i]);
        }
    }
    return 0;
}