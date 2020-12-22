//
// Created by ca1se on 2020/12/13.
//

#ifndef DEMO2_2_MaintainMachine_H
#define DEMO2_2_MaintainMachine_H

#include "machine.h"
#include <memory>

enum state {
    no_five_dime,
    lack_five_dime,
    no_one_yuan,
    lack_one_yuan,
};

class MaintainMachine {
public:
    explicit MaintainMachine(Machine* pM);
    ~MaintainMachine() = default;

    void InitMachine(std::string&& addr);

    size_t GetGoodsRemain(const Gname& name) const;

    std::vector<state> GetMachineState() const;
private:
    Machine* _pMachine;

};


#endif //DEMO2_2_MaintainMachine_H
