//
// Created by ca1se on 2020/12/13.
//

#include "explain.h"
#include <cstdio>
#include <cstring>

explain::explain(const std::string &addr, std::string &&t1, std::string &&t2, std::string&& t3):
        _plF(fopen(addr.c_str(), "r"))
        ,_e1(t1)
        ,_e2(t2)
        ,_e3(t3)
        ,_pTPair(nullptr)
        ,_pDPair(nullptr)
        ,_ptCounter(nullptr)
        ,_pdCounter(nullptr)
{
    if (_plF == nullptr){
        std::terminate();
    }
}

explain::~explain() {
    if(_plF){
        fclose(_plF);
    }

    ResetTCounter();
    ResetDCounter();

    if(_pdCounter){
        _pDPair->clear();
        _pdCounter = nullptr;
        _pDPair = nullptr;
    }
    if(_ptCounter){
        _pTPair->clear();
        _ptCounter = nullptr;
        _pTPair = nullptr;
    }
}

std::pair<std::string, std::string> explain::ExplainInTurn_pair() {
    static size_t counter = 0;
    static std::vector<std::pair<std::string, std::string>> fromList;
    _pdCounter = &counter;
    _pDPair = &fromList;

    bool foundKey = false;
    std::string elementF;

    while (!counter) {
        char buf[80] = {0};
        int res = fscanf(_plF, "%s", buf);
        if (res != EOF) {
            if (!foundKey) {
                if (!strncmp(buf + 1, _e1.c_str(), _e1.size()) && *(buf + _e1.size() + 1) == '\"') {
                    elementF = FindValue(_plF);
                    foundKey = true;
                }
            } else {
                if (!strncmp(buf + 1, _e2.c_str(), _e2.size()) && *(buf + _e2.size() + 1) == '\"') {
                    fromList.emplace_back(elementF, FindValue(_plF));
                    foundKey = false;
                }
            }
        } else {
            break;
        }
    }

    if(counter < fromList.size()){
        return fromList[counter++];
    }else{
        return std::make_pair("", "");
    }
}

tpair<std::string, std::string, std::string> explain::ExplainInTurn_tpair() {
    if(!(_e3.length())){
        std::terminate();
    }
    static size_t counter = 0;
    static std::vector<tpair<std::string, std::string, std::string>> fromList;
    _ptCounter = &counter;
    _pTPair = &fromList;

    bool foundE1 = false;
    bool foundE2 = false;
    std::string element1;
    std::string element2;

    while (!counter){
        char buf[80] = {0};
        int res = fscanf(_plF, "%s", buf);
        if(res != EOF) {
            if (!foundE1) {
                if (!strncmp(buf + 1, _e1.c_str(), _e1.size()) && *(buf + _e1.size() + 1) == '\"') {
                    element1 = FindValue(_plF);
                    foundE1 = true;
                }
            } else if (!foundE2) {
                if (!strncmp(buf + 1, _e2.c_str(), _e2.size()) && *(buf + _e2.size() + 1) == '\"') {
                    element2 = FindValue(_plF);
                    foundE2 = true;
                }
            } else {
                if (!strncmp(buf + 1, _e3.c_str(), _e3.size()) && *(buf + _e3.size() + 1) == '\"') {
                    fromList.emplace_back(element1, element2, FindValue(_plF));
                    foundE2 = foundE1 = false;
                }
            }
        }else{
            break;
        }
    }

    if(counter < fromList.size()){
        return fromList[counter++];
    }else{
        return tpair<std::string, std::string, std::string>("", "", "");
    }
}

std::string explain::FindValue(FILE *fp) {
    char buf[80] = {0};
    char t[80] = {0};
    while (fscanf(fp, "%s", buf) && buf[0] != '\"');
    strncpy(t, buf + 1, strchr(buf + 1, '\"') - buf - 1);
    return t;
}

void explain::ResetDCounter() {
    if(_pdCounter){
        *_pdCounter = 0;
    }
}

void explain::ResetTCounter() {
    if(_ptCounter){
        *_ptCounter = 0;
    }
}