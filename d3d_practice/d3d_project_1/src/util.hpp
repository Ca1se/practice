#ifndef UTIL_HPP
#define UTIL_HPP


#define RELEASE_COM(x) \
    if(x) { \
        x->Release(); \
        x = nullptr; \
    }

#define HR_B(function, ...) \
{ \
    HRESULT hr = function(__VA_ARGS__); \
    if(FAILED(hr)) { \
        LOG_ERROR(#function " Failed."); \
        return false; \
    } \
}

#define HR_V(function, ...) \
{ \
    HRESULT hr = function(__VA_ARGS__); \
    if(FAILED(hr)) { \
        LOG_ERROR(#function " Failed."); \
        return; \
    } \
}

#endif // util.hpp