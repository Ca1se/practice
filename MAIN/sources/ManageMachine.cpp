//
// Created by ca1se on 2020/12/13.
//

#include "ManageMachine.h"
#include "explain.h"

ManageMachine::ManageMachine(): _pMachine(new Machine){
    InitMachine("/home/ca1se/CLionProjects/CoursDesign/list/goods.list");
}

void ManageMachine::InitMachine(std::string&& addr) {

}