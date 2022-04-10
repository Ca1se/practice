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
        if(it.first == "dime_five"){
            c = coin::dime_five;
        }else if(it.first == "yuan_one"){
            c = coin::yuan_one;
        }
        _pMachine->_pCoins->emplace_back(std::make_pair(c, strtol(it.second.c_str(), nullptr, 10)));
    }

    delete pC;
}

size_t MaintainMachine::GetGoodsRemain(const Gname& g) const {
    return _pMachine->GoodsRemain(g);
}

std::vector<state> MaintainMachine::GetMachineState() const {
    auto& vCoins = *(_pMachine->_pCoins);
    std::vector<state> vS;
    for(auto& it: vCoins){
        if(it.first == coin::yuan_one){
            if(it.second == 0)
                vS.push_back(state::no_one_yuan);
            else if(it.second < 20)
                vS.push_back(state::lack_one_yuan);
        }else{
            if(it.second == 0)
                vS.push_back(state::no_five_dime);
            else if(it.second < 20)
                vS.push_back(state::lack_five_dime);
        }
    }
    return vS;
}