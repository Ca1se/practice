//
// Created by ca1se on 2020/12/13.
//

#ifndef COURSEDESIGN_DEAL_MAINTAIN_H
#define COURSEDESIGN_DEAL_MAINTAIN_H

#include "machine.h"
#include "log.h"
#include <ctime>         //时间头文件
#include <list>             //日志

class Pay {
private:
    Machine* _pM;
public:
    Pay(Machine* pM);
    void PaymentOffline(Gname, size_t, const std::list<std::pair<coin,size_t> >&) const;
    void PaymentOnline(Gname, size_t, std::string) const;
};

class ContainUpdate {
private:
    Machine* _pM;
public:
    ContainUpdate(Machine* pM);        //构造函数有个指针
    void ReplenishCoin(coin, size_t) const;
    void ReplenishGoods(Gname, size_t) const;
};

class Time {
public:
    static const char* GetTimeNow();            //静态常量函数，好让所有其他的一起公用
};

#endif //COURSEDESIGN_DEAL_MAINTAIN_H
