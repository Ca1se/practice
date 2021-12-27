#include "utils.hh"
#include <cstdint>

int64_t generateSessionId() {
    return (int64_t) time(nullptr);
}