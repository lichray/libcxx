// -*- C++ -*-
//===--------------------- support/itoa/itoa.h ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_SUPPORT_ITOA_ITOA_H
#define _LIBCPP_SUPPORT_ITOA_ITOA_H

#include <__config>
#include <type_traits>
#include <limits>
#include <stdint.h>

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __itoa
{

#if __has_builtin(__builtin_clzll)

inline _LIBCPP_INLINE_VISIBILITY auto
__u64digits10(uint64_t __x) -> int
{
    constexpr uint64_t __pow10[] = {
        UINT64_C(0),
        UINT64_C(10),
        UINT64_C(100),
        UINT64_C(1000),
        UINT64_C(10000),
        UINT64_C(100000),
        UINT64_C(1000000),
        UINT64_C(10000000),
        UINT64_C(100000000),
        UINT64_C(1000000000),
        UINT64_C(10000000000),
        UINT64_C(100000000000),
        UINT64_C(1000000000000),
        UINT64_C(10000000000000),
        UINT64_C(100000000000000),
        UINT64_C(1000000000000000),
        UINT64_C(10000000000000000),
        UINT64_C(100000000000000000),
        UINT64_C(1000000000000000000),
        UINT64_C(10000000000000000000),
    };

    auto __t = (64 - __builtin_clzll(__x | 1)) * 1233 >> 12;
    return __t - (__x < __pow10[__t]) + 1;
}

inline _LIBCPP_INLINE_VISIBILITY auto
__u32digits10(uint32_t __x) -> int
{
    constexpr uint32_t __pow10[] = {
        UINT32_C(0),          UINT32_C(10),       UINT32_C(100),
        UINT32_C(1000),       UINT32_C(10000),    UINT32_C(100000),
        UINT32_C(1000000),    UINT32_C(10000000), UINT32_C(100000000),
        UINT32_C(1000000000),
    };

    auto __t = (32 - __builtin_clz(__x | 1)) * 1233 >> 12;
    return __t - (__x < __pow10[__t]) + 1;
}

#endif

extern _LIBCPP_FUNC_VIS char* __u64toa(uint64_t __value, char* __buffer);
extern _LIBCPP_FUNC_VIS char* __u32toa(uint32_t __value, char* __buffer);

template <typename _Tp, typename = void>
struct _LIBCPP_HIDDEN traits
{
    static constexpr int digits = numeric_limits<_Tp>::digits10 + 1;

#if __has_builtin(__builtin_clzll)
    static _LIBCPP_INLINE_VISIBILITY auto width(_Tp __v) -> int
    {
        return __u64digits10(__v);
    }
#endif

    static _LIBCPP_INLINE_VISIBILITY auto convert(_Tp __v, char* __p) -> char*
    {
        return __u64toa(__v, __p);
    }
};

template <typename _Tp>
struct _LIBCPP_HIDDEN traits<_Tp, decltype(void(uint32_t{declval<_Tp>()}))>
{
    static constexpr int digits = numeric_limits<_Tp>::digits10 + 1;

#if __has_builtin(__builtin_clzll)
    static _LIBCPP_INLINE_VISIBILITY auto width(_Tp __v) -> int
    {
        return __u32digits10(__v);
    }
#endif

    static _LIBCPP_INLINE_VISIBILITY auto convert(_Tp __v, char* __p) -> char*
    {
        return __u32toa(__v, __p);
    }
};

}  // namespace __itoa

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_SUPPORT_ITOA_ITOA_H
