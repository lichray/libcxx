//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03
// <charconv>

// to_chars_result to_chars(char* first, char* last, Integral value,
//                          int base = 10)

#include "charconv_test_helpers.h"

template <typename T>
struct test_basics : to_chars_test_base<T>
{
    using to_chars_test_base<T>::test;
    using to_chars_test_base<T>::test_value;

    void operator()()
    {
        test(0, "0", 10);
        test(42, "42", 10);
        test(32768, "32768", 10);
        test(0xf, "f", 16);
        test(0xdeadbeaf, "deadbeaf", 16);
        test(0755, "755", 8);

        for (int b = 2; b < 37; ++b)
        {
            using xl = std::numeric_limits<T>;

            test_value(1, b);
            test_value(xl::lowest(), b);
            test_value((xl::max)(), b);
            test_value((xl::max)() / 2, b);
        }
    }
};

template <typename T>
struct test_signed : to_chars_test_base<T>
{
    using to_chars_test_base<T>::test;
    using to_chars_test_base<T>::test_value;

    void operator()()
    {
        test(-1, "-1", 10);
        test(-12, "-12", 10);
        test(-21734634, "-21734634", 10);
        test(-2647, "-101001010111", 2);
        test(-0xcc1, "-cc1", 16);

        for (int b = 2; b < 37; ++b)
        {
            using xl = std::numeric_limits<T>;

            test_value(0, b);
            test_value(xl::lowest(), b);
            test_value((xl::max)(), b);
        }
    }
};

int
main()
{
    auto all_signed =
        type_list<char, signed char, short, int, long, long long>();
    auto all_unsigned = type_list<unsigned char, unsigned short, unsigned int,
                                  unsigned long, unsigned long long>();
    auto integrals = concat(all_signed, all_unsigned);

    run<test_basics>(integrals);
    run<test_signed>(all_signed);
}
