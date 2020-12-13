//
// Created by ca1se on 2020/12/13.
//

#ifndef DEMO2_2_MANAGEMACHINE_H
#define DEMO2_2_MANAGEMACHINE_H

#include "temp.h"

class  ManageMachine {
public:
    ManageMachine();
    ~ManageMachine() = default;

    void InitMachine(std::string&& addr);

    void AddCoin(coin, size_t);
    void AddGoods(Gstring, size_t);
    int TakeOutGoods(Gstring);      //返回1为正常， 返回0为缺货
    size_t GoodsCost(Gstring) const;
    static ManageMachine& Get();
private:
    std::unique_ptr<Machine> _pMachine;
};


#endif //DEMO2_2_MANAGEMACHINE_H
