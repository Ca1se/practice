// This file is part of the t7 renderer project.
// Copyleft 2023, typr7. All wrongs reserved.

#ifndef LOG_HPP
#define LOG_HPP


#include <string>
#include <ctime>
#include <cstdio>


#define LOG_AUX_FORMAT(format, level, file) \
    "[%s][" level "][" file "][%d]: " format "\n"

#if defined (DEBUG) || defined (_DEBUG)
    #define LOGFMT_DEBUG(format, ...)   t7log::log_format(LOG_AUX_FORMAT(format, "DEBUG", FILE_BASENAME), __LINE__, ##__VA_ARGS__)
#else
    #define LOGFMT_DEBUG(format, ...)   ;
#endif

#define LOGFMT_INFO(format, ...)        t7log::log_format(LOG_AUX_FORMAT(format, "INFO", FILE_BASENAME), __LINE__, ##__VA_ARGS__)
#define LOGFMT_ERROR(format, ...)       t7log::log_format(LOG_AUX_FORMAT(format, "ERROR", FILE_BASENAME), __LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(log)  LOGFMT_DEBUG(log)
#define LOG_INFO(log)   LOGFMT_INFO(log)
#define LOG_ERROR(log)  LOGFMT_ERROR(log)


inline std::string get_current_time() {
    time_t t = time(nullptr);
    tm tm;

    gmtime_s(&tm, &t);

    char buf[20];
    sprintf(buf, "%d/%02d/%02d %02d:%02d:%02d", 
        tm.tm_year + 1900, 
        tm.tm_mon + 1, 
        tm.tm_mday, 
        tm.tm_hour, 
        tm.tm_min, 
        tm.tm_sec);

    return std::string(buf);
}

namespace t7log {

template <typename ...Args>
void log_format(const char* format, Args... args) {
    std::string cur_time = get_current_time();

    printf(format, cur_time.c_str(), args...);
}

}

#endif // log.hpp