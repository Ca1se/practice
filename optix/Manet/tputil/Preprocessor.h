#pragma once

#if defined(__CUDACC__) || defined(__CUDABE__)
    #define TPUTIL_INLINE __forceinline__
    #define TPUTIL_HOST   __host__
    #define TPUTIL_DEVICE __device__
#else
    #define TPUTIL_INLINE inline
    #define TPUTIL_HOST
    #define TPUTIL_DEVICE
#endif

#define TPUTIL_HOSTDEVICE TPUTIL_HOST TPUTIL_DEVICE
#define TPUTIL_DECL TPUTIL_INLINE TPUTIL_HOSTDEVICE