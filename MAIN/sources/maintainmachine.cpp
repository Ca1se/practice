//
// Created by ca1se on 2020/12/13.
//

#include "maintainmachine.h"
#include "explain.h"
#include <cstdlib>


MaintainMachine::MaintainMachine(Machine* pM): _pMachine(pM) {}


void MaintainMachine::InitMachine(std::string&& addr) {
    auto *pG = new explain(addr, "name", "cost", "remain");
    for (size_t i = 0; i < 9; i++) {
        auto it = pG->ExplainInTurn_tpair();
        _pMachine->_gToPos.insert(std::make_pair(it.first, i));
        _pMachine->_pGoods->emplace_back(std::make_pair(Goods(std::move(it.first), strtod(it.second.c_str(), nullptr)), \
                                                                        strtol(it.third.c_str(), nullptr, 10)));
    }
    delete pG;

    auto *pC = new explain(addr, "coin", "remain");
    for(size_t i = 0; i < 2; i++){
        auto it = pC->ExplainInTurn_pair();
        coin c;
        if(it.first == "five_dime"){
            c = coin::dime_five;
        }else if(it.first == "one_yuan"){
            c = coin::yuan_one;
        }
        _pMachine->_pCoins->emplace_back(std::make_pair(c, strtol(it.second.c_str(), nullptr, 10)));
    }

    delete pC;
}

size_t MaintainMachine::GetGoodsRemain(const Gname& g) const {
    return _pMachine->GoodsRemain(g);
}