//
// Created by ca1se on 2020/12/13.
//

#ifndef COURSEDESIGN_LOG_H
#define COURSEDESIGN_LOG_H

#include <fstream>

#define PLOG Log::GetStream(0)// pay log stream
#define MLOG Log::GetStream(1)// maintain log stream

class Log {
public:
    Log();
    ~Log();
    static std::ofstream& GetStream(int);
private:
    std::ofstream _logDeal;
    std::ofstream _logMaintain;
};


#endif //COURSEDESIGN_LOG_H
