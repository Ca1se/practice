//
// Created by ca1se on 2020/12/13.
//

#include "machine.h"
#include <algorithm>
#include <fstream>

Machine::Machine(): _pGoods(new std::vector<std::pair<Goods, size_t> >)
        , _pCoins(new std::vector<std::pair<coin, size_t> >) {}
Machine::~Machine() {
    StateOutput();
    if (_pGoods){
        delete _pGoods;
        _pGoods = nullptr;
    }
    if (_pCoins){
        delete _pCoins;
        _pCoins = nullptr;
    }
}

size_t Machine::GoodsRemain(Gname g) {
    size_t pos = _gToPos[g];
    return (*_pGoods)[pos].second;
}

size_t Machine::CoinRemain(coin c) const {
    for(auto& it: *_pCoins){
        if(it.first == c)
            return it.second;
    }
    std::terminate();
}

void Machine::SetGoods(Gname g, size_t n) {
    size_t pos = _gToPos[g];
    (*_pGoods)[pos].second = n;
}

void Machine::SetCoins(coin c, size_t n) {
    for(auto& it: *_pCoins){
        if(it.first == c){
            it.second = n;
            return;
        }
    }
}

void Machine::StateOutput() const {
    std::ofstream ofs("list/goods.json", std::ios::trunc);
    char buf[128] = {0};
    ofs << "{\n"
           "\t\"goodsList\": {\n";
    for(size_t i = 0; i < _pGoods->size(); i++){
        auto& goods = (*_pGoods)[i].first;
        size_t remain = (*_pGoods)[i].second;
        sprintf(buf, "\t\t\"%zu\": { \"name\": \"%s\", \"cost\": \"%.1f\", \"remain\": \"%zu\" }", i, goods.name.c_str(), goods.cost, remain);
        ofs << buf;
        if(i != (_pGoods->size() - 1))
            ofs << ',';
        ofs << '\n';
    }
    ofs << "\t},\n"
           "\t\"coinsList:\": {\n";
    for(size_t i = 0; i < _pCoins->size(); i++){
        auto& coin = (*_pCoins)[i].first;
        size_t remain = (*_pCoins)[i].second;
        char t[30] = {0};
        if(coin == coin::yuan_one){
            sprintf(t, "yuan_one");
        }else{
            sprintf(t, "dime_five");
        }
        sprintf(buf, "\t\t\"%zu\": { \"coin\": \"%s\", \"remain\": \"%zu\" }", i, t, remain);
        ofs << buf;
        if(i != (_pCoins->size() - 1))
            ofs << ',';
        ofs << '\n';
    }
    ofs << "\t}\n"
           "}\n";

    ofs.close();
}

Machine & Machine::Get() {
    static Machine m;
    return m;
}