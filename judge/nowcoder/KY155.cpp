#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

static const int maxn = 500 + 5;
int num;
double cmax, dist, dista, cnow = 0, dnow = 0, ans = 0;
std::pair<double, double> record[maxn];
struct Gas
{
    double price;
    double store;
    bool operator<(const Gas& other) const noexcept
    {
        return price >= other.price;
    }
};
std::set<Gas> s;

inline double use_gas(double d)
{
    Gas a, b;
    while(!s.empty()) {
        auto low = --s.end();
        if(low->store * dista >= d) {
            if(low->store * dista > d)
                s.insert(Gas{low->price, low->store - (d / dista)});
            ans += low->price * d / dista;
            d = 0;
            s.erase(low);
            return d;
        }else {
            ans += low->store * low->price;
            d -= low->store * dista;
            s.erase(low);
        }
    }
    return d;
}

inline void replace_gas(double price)
{
    for(auto it = s.begin(); it != s.end() && it->price > price;) {
        cnow -= it->store;
        it = s.erase(it);
    }

    s.insert(Gas{price, cmax - cnow});
    cnow = cmax;
}

int main() {
    while(std::scanf("%lf%lf%lf%d", &cmax, &dist, &dista, &num) != EOF) {
        s.clear();
        cnow = dnow = ans = 0;
        for (int i = 0; i < num; i++)
            scanf("%lf%lf", &record[i].first, &record[i].second);
        std::sort(record, record + num, [](std::pair<double, double> a, std::pair<double, double> b) {
            return a.second < b.second;
        });
        if(record[0].second != 0) {
            printf("The maximum travel distance = 0.00\n");
            continue;
        }
        s.insert(Gas{record[0].first, cmax});
        cnow = cmax;
        for(int i = 1; i < num && record[i].second < dist; i++) {
            double rd = use_gas(record[i].second - record[i - 1].second);
            if(rd == 0) {
                dnow = record[i].second;
                cnow -= (record[i].second - record[i - 1].second) / dista;
                replace_gas(record[i].first);
            }else {
                printf("The maximum travel distance = %.2f\n", record[i].second - rd);
                goto l;
            }
        }
    
        {
            double rd = use_gas(dist - dnow);
            if(rd == 0) {
                printf("%.2f\n", ans);
            }else {
                printf("The maximum travel distance = %.2f\n", dist - rd);
            }
        }
        l:;
    }
    
    return 0;
}