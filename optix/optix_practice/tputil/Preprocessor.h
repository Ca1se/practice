#pragma once

#if defined(__CUDACC__) || defined(__CUDABE__)
#    define TPUTIL_HOSTDEVICE __host__ __device__
#    define TPUTIL_INLINE     __forceinline__
#else
#    define TPUTIL_HOSTDEVICE
#    define TPUTIL_INLINE inline
#endif