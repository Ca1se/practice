//
// Created by ca1se on 2020/12/13.
//

#ifndef COURSEDESIGN_MACHINE_H
#define COURSEDESIGN_MACHINE_H

#include <string>
#include <map>
#include <vector>

#define MANAGED friend class MaintainMachine;

typedef std::string Gname;

//嘉乐部分
enum coin {
    dime_five = 5,
    yuan_one = 10,
};//实际面额要除10

struct Goods {
    Goods(Gname&& name, double cost): name(name), cost(cost) {}
    std::string name;
    double cost;
};

class Machine {
public:
    MANAGED

    ~Machine();

    static Machine& Get();

    size_t GoodsRemain(Gname) const;
    size_t CoinRemain(coin) const;

    void SetGoods(Gname, size_t);
    void SetCoins(coin, size_t);
private:
    Machine(): _pGoods(new std::vector<std::pair<Goods, size_t> >)
            , _pCoins(new std::vector<std::pair<coin, size_t> >) {}

    std::vector<std::pair<Goods, size_t> >* _pGoods;
    std::vector<std::pair<coin, size_t> >* _pCoins;
    std::map<Gname, size_t> _gToPos;// 货物到向量下标的映射
};

#endif //COURSEDESIGN_MACHINE_H
