//
// Created by ca1se on 2020/12/13.
//

#include "machine.h"

Machine & Machine::Get() {
    static Machine m;
    return m;
}