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

static constexpr uint64_t __pow10_64[] = {
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

static constexpr uint32_t __pow10_32[] = {
    UINT32_C(0),          UINT32_C(10),       UINT32_C(100),
    UINT32_C(1000),       UINT32_C(10000),    UINT32_C(100000),
    UINT32_C(1000000),    UINT32_C(10000000), UINT32_C(100000000),
    UINT32_C(1000000000),
};

_LIBCPP_FUNC_VIS char* __u64toa(uint64_t __value, char* __buffer);
_LIBCPP_FUNC_VIS char* __u32toa(uint32_t __value, char* __buffer);

template <typename _Tp, typename = void>
struct _LIBCPP_HIDDEN __traits_base
{
    using type = uint64_t;

#if !defined(_LIBCPP_COMPILER_MSVC)
    static _LIBCPP_INLINE_VISIBILITY auto width(_Tp __v) -> int
    {
        auto __t = (64 - __builtin_clzll(__v | 1)) * 1233 >> 12;
        return __t - (__v < __pow10_64[__t]) + 1;
    }
#endif

    static _LIBCPP_INLINE_VISIBILITY auto convert(_Tp __v, char* __p) -> char*
    {
        return __u64toa(__v, __p);
    }

    static _LIBCPP_INLINE_VISIBILITY auto pow() -> type const (&)[20]
    {
        return __pow10_64;
    }
};

template <typename _Tp>
struct _LIBCPP_HIDDEN
    __traits_base<_Tp, decltype(void(uint32_t{declval<_Tp>()}))>
{
    using type = uint32_t;

#if !defined(_LIBCPP_COMPILER_MSVC)
    static _LIBCPP_INLINE_VISIBILITY auto width(_Tp __v) -> int
    {
        auto __t = (32 - __builtin_clz(__v | 1)) * 1233 >> 12;
        return __t - (__v < __pow10_32[__t]) + 1;
    }
#endif

    static _LIBCPP_INLINE_VISIBILITY auto convert(_Tp __v, char* __p) -> char*
    {
        return __u32toa(__v, __p);
    }

    static _LIBCPP_INLINE_VISIBILITY auto pow() -> type const (&)[10]
    {
        return __pow10_32;
    }
};

template <typename _Tp>
inline _LIBCPP_INLINE_VISIBILITY bool
__mul_overflowed(unsigned char __a, _Tp __b, unsigned char& __r)
{
    auto __c = __a * __b;
    __r = __c;
    return __c > (numeric_limits<unsigned char>::max)();
}

template <typename _Tp>
inline _LIBCPP_INLINE_VISIBILITY bool
__mul_overflowed(unsigned short __a, _Tp __b, unsigned short& __r)
{
    auto __c = __a * __b;
    __r = __c;
    return __c > (numeric_limits<unsigned short>::max)();
}

template <typename _Tp>
inline _LIBCPP_INLINE_VISIBILITY bool
__mul_overflowed(_Tp __a, _Tp __b, _Tp& __r)
{
    static_assert(is_unsigned<_Tp>::value, "");
#if !defined(_LIBCPP_COMPILER_MSVC)
    return __builtin_mul_overflow(__a, __b, &__r);
#else
    bool __did = __b && ((numeric_limits<_Tp>::max)() / __b) < __a;
    __r = __a * __b;
    return __did;
#endif
}

template <typename _Tp, typename _Up>
inline _LIBCPP_INLINE_VISIBILITY bool
__mul_overflowed(_Tp __a, _Up __b, _Tp& __r)
{
    return __mul_overflowed(__a, static_cast<_Tp>(__b), __r);
}

template <typename _Tp>
struct _LIBCPP_HIDDEN traits : __traits_base<_Tp>
{
    static constexpr int digits = numeric_limits<_Tp>::digits10 + 1;
    using __traits_base<_Tp>::pow;
    using typename __traits_base<_Tp>::type;

    // precondition: at least one non-zero character available
    static _LIBCPP_INLINE_VISIBILITY auto
    read(char const* __p, char const* __ep, type& __a, type& __b) -> char const*
    {
        type __cprod[digits];
        int __j = digits - 1;
        int __i = digits;
        do
        {
            if (!('0' <= *__p && *__p <= '9'))
                break;
            __cprod[--__i] = *__p++ - '0';
        } while (__p != __ep && __i != 0);

        __a = inner_product(__cprod + __i + 1, __cprod + __j, pow() + 1,
                            __cprod[__i]);
        if (__mul_overflowed(__cprod[__j], pow()[__j - __i], __b))
            --__p;
        return __p;
    }

    template <typename _It1, typename _It2, class _Up>
    static _LIBCPP_INLINE_VISIBILITY auto
    inner_product(_It1 __first1, _It1 __last1, _It2 __first2, _Up __init) -> _Up
    {
        for (; __first1 < __last1; ++__first1, ++__first2)
            __init = __init + *__first1 * *__first2;
        return __init;
    }
};

}  // namespace __itoa

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_SUPPORT_ITOA_ITOA_H
