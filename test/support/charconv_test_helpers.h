//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef SUPPORT_CHARCONV_TEST_HELPERS_H
#define SUPPORT_CHARCONV_TEST_HELPERS_H

#include <charconv>
#include <cassert>
#include <limits>
#include <string.h>
#include <stdlib.h>

#include "test_macros.h"

using std::false_type;
using std::true_type;

template <typename To, typename From>
constexpr auto
is_non_narrowing(From a) -> decltype(To{a}, true_type())
{
    return {};
}

template <typename To>
constexpr auto
is_non_narrowing(...) -> false_type
{
    return {};
}

template <typename X, typename T>
constexpr bool
_fits_in(T, true_type /* non-narrowing*/, ...)
{
    return true;
}

template <typename X, typename T, typename xl = std::numeric_limits<X>>
constexpr bool
_fits_in(T v, false_type, true_type /* T signed*/, true_type /* X signed */)
{
    return xl::lowest() <= v && v <= (xl::max)();
}

template <typename X, typename T, typename xl = std::numeric_limits<X>>
constexpr bool
_fits_in(T v, false_type, true_type /* T signed */, false_type /* X unsigned*/)
{
    return 0 <= v && typename std::make_unsigned<T>::type(v) <= (xl::max)();
}

template <typename X, typename T, typename xl = std::numeric_limits<X>>
constexpr bool
_fits_in(T v, false_type, false_type /* T unsigned */, ...)
{
    return v <= typename std::make_unsigned<X>::type((xl::max)());
}

template <typename X, typename T>
constexpr bool
fits_in(T v)
{
    return _fits_in<X>(v, is_non_narrowing<X>(v), std::is_signed<T>(),
                       std::is_signed<X>());
}

template <typename X>
struct to_chars_test_base
{
    template <typename T, size_t N, typename... Ts>
    void test(T v, char const (&expect)[N], Ts... args)
    {
        using std::to_chars;
        std::to_chars_result r;

        constexpr size_t len = N - 1;
        static_assert(len > 0, "expected output won't be empty");

        if (!fits_in<X>(v))
            return;

        r = to_chars(buf, buf + len - 1, X(v), args...);
        LIBCPP_ASSERT(r.ptr == buf + len - 1);
        LIBCPP_ASSERT(r.ec == std::errc::value_too_large);

        r = to_chars(buf, buf + sizeof(buf), X(v), args...);
        LIBCPP_ASSERT(r.ptr == buf + len);
        LIBCPP_ASSERT(r.ec == std::errc{});
        LIBCPP_ASSERT(memcmp(buf, expect, len) == 0);
    }

    template <typename... Ts>
    void test_value(X v, Ts... args)
    {
        using std::to_chars;
        std::to_chars_result r;

        r = to_chars(buf, buf + sizeof(buf), v, args...);
        LIBCPP_ASSERT(r.ec == std::errc{});
        *r.ptr = '\0';

        auto a = fromchars(buf, r.ptr, args...);
        LIBCPP_ASSERT(v == a);

        auto ep = r.ptr - 1;
        r = to_chars(buf, ep, v, args...);
        LIBCPP_ASSERT(r.ptr == ep);
        LIBCPP_ASSERT(r.ec == std::errc::value_too_large);
    }

private:
    using max_t = typename std::conditional<std::is_signed<X>::value, long long,
                                            unsigned long long>::type;

    static auto fromchars(char const* p, char const* ep, int base, true_type)
        -> long long
    {
        char* last;
        auto r = strtoll(p, &last, base);
        LIBCPP_ASSERT(last == ep);

        return r;
    }

    static auto fromchars(char const* p, char const* ep, int base, false_type)
        -> unsigned long long
    {
        char* last;
        auto r = strtoull(p, &last, base);
        LIBCPP_ASSERT(last == ep);

        return r;
    }

    static auto fromchars(char const* p, char const* ep, int base = 10) -> max_t
    {
        return fromchars(p, ep, base, std::is_signed<X>());
    }

    char buf[100];
};

template <typename... T>
struct type_list
{
};

template <typename L1, typename L2>
struct type_concat;

template <typename... Xs, typename... Ys>
struct type_concat<type_list<Xs...>, type_list<Ys...>>
{
    using type = type_list<Xs..., Ys...>;
};

template <typename L1, typename L2>
using concat_t = typename type_concat<L1, L2>::type;

template <typename L1, typename L2>
constexpr auto concat(L1, L2) -> concat_t<L1, L2>
{
    return {};
}

template <template <typename> class Fn, typename... Ts>
void
run(type_list<Ts...>)
{
    int ls[sizeof...(Ts)] = {(Fn<Ts>{}(), 0)...};
    (void)ls;
}

#endif  // SUPPORT_CHARCONV_TEST_HELPERS_H
