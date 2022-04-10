//
// Created by ca1se on 2020/12/13.
//

#include "log.h"

Log::Log():_logDeal("log/deal.log", std::ios::app), _logMaintain("log/maintain.log", std::ios::app) {}
Log::~Log() {
    _logDeal.close();
    _logMaintain.close();
}

std::ofstream & Log::GetStream(int c) {
    static Log log;
    if (c){
        return log._logMaintain;
    }else{
        return log._logDeal;
    }
}