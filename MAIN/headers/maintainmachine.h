//
// Created by ca1se on 2020/12/13.
//

#ifndef DEMO2_2_MaintainMachine_H
#define DEMO2_2_MaintainMachine_H

#include "machine.h"
#include <memory>

class MaintainMachine {
public:
    explicit MaintainMachine(Machine* pM);
    ~MaintainMachine() = default;

    size_t GoodsCost(const Gname&) const; //for GUI
    void InitMachine(std::string&& addr);

private:
    Machine* _pMachine;

};


#endif //DEMO2_2_MaintainMachine_H
