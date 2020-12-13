#include<string>
#include<fstream>
#include<memory>
#include<list>
#include<vector>
#include<map>

#define PLOG Log::GetStream(0)// pay log stream
#define MLOG Log::GetStream(1)// maintain log stream
#define MAINTAIN friend class maintain;

typedef unsigned long long ull;
typedef std::string Gstring;

//嘉乐部分
enum coin {
    dime_five = 5,
    yuan_one = 10,
};//实际面额要除10

class Machine {
public:
    MAINTAIN

    struct Goods {
        std::string name;
        ull cost;
    };
    Machine(): _pGoods(new std::vector<std::pair<Goods, size_t> >(9))
             , _pCoins(new std::vector<std::pair<coin, size_t> >(2)) {}
    ~Machine();

    size_t GoodsRemain(Gstring) const;
    size_t CoinRemain(coin) const;

    void SetGoods(Gstring, size_t);
    void SetCoins(coin, size_t);
private:
    std::vector<std::pair<Goods, size_t> >* _pGoods;
    std::vector<std::pair<coin, size_t> >* _pCoins;
    std::map<std::string, size_t> _gToPos;// 货物到向量下标的映射
};


class Log {
public:
    Log(): _logDeal("/log/deal.log"), _logMaintain("/log/trace.log") {}
    ~Log();
    static std::ofstream& GetStream();
private:
    std::ofstream _logDeal;
    std::ofstream _logMaintain;
};






//光平部分
class Pay {
private:
    M* _pM;
public:
    Pay(MachineMaintain* pM): _pM(pM) {}
    int PaymentOffline(Gstring, std::list<std::pair<coin,size_t> >) const;
    int PaymentOnline(Gstring) const;
};

class ContainUpdate {
private:
    MachineMaintain* _pM;
public:
    ContainUpdate(MachineMaintain* pM): _pM(pM) {}
    void ReplenishCoin(coin, size_t) const;
    void ReplenishGoods(Gstring, size_t) const;
};
