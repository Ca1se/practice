//
// Created by ca1se on 2020/12/13.
//

#include "machine.h"
#include <algorithm>

Machine::Machine(): _pGoods(new std::vector<std::pair<Goods, size_t> >)
        , _pCoins(new std::vector<std::pair<coin, size_t> >) {}
Machine::~Machine() {
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
}

void Machine::SetGoods(Gname g, size_t n) {
    size_t pos = _gToPos[g];
    (*_pGoods)[pos].second = n;
}

void Machine::SetCoins(coin c, size_t n) {
    for(auto& it: *_pCoins){
        if(it.first == c){
            it.second = n;
            return;;
        }
    }
}

Machine & Machine::Get() {
    static Machine m;
    return m;
}