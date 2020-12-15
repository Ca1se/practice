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

    void InitMachine(std::string&& addr);

    size_t GetGoodsRemain(const Gname& name) const;
private:
    Machine* _pMachine;

};


#endif //DEMO2_2_MaintainMachine_H
