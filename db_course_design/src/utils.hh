#ifndef _UTILS_HH_
#define _UTILS_HH_

#include <oatpp/core/Types.hpp>
#include <ctime>
#include <cstdint>

int64_t generateSessionId();

int64_t getCookieVal(const oatpp::String& cookie, const std::string& name);

#endif