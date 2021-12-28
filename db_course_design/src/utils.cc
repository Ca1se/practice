#include "utils.hh"
#include <cstdint>

int64_t generateSessionId() {
    return (int64_t) time(nullptr);
}

int64_t getSessionId(const oatpp::String& cookie) {
    return std::atoi(cookie->substr(cookie->find("session_id") + 11).c_str());
}