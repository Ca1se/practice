#include "utils.hh"
#include <cstdint>

int64_t generateSessionId() {
    return (int64_t) time(nullptr);
}

int64_t getCookieVal(const oatpp::String& cookie, const std::string& name) {
    int pos = cookie->find(name);
    int cpos;
    if((cpos = cookie->find(";", pos)) != std::string::npos) {
        return std::atoi(cookie->substr(pos + name.size() + 1, cpos - pos - name.size() - 1).c_str());
    }else {
        return std::atoi(cookie->substr(pos + name.size() + 1).c_str());
    }
}