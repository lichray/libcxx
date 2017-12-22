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

// from_chars_result from_chars(const char* first, const char* last,
//                              Integral& value, int base = 10)

#include "charconv_test_helpers.h"

template <typename T>
struct test_basics : roundtrip_test_base<T>
{
    using roundtrip_test_base<T>::test;

    void operator()()
    {
        test(0);
        test(42);
        test(32768);
        test(0, 10);
        test(42, 10);
        test(32768, 10);
        test(0xf, 16);
        test(0xdeadbeaf, 16);
        test(0755, 8);

        for (int b = 2; b < 37; ++b)
        {
            using xl = std::numeric_limits<T>;

            test(1, b);
            test(xl::lowest(), b);
            test((xl::max)(), b);
            test((xl::max)() / 2, b);
        }

        using std::from_chars;
        std::from_chars_result r;
        T x;

        {
            char s[] = "001x";

            // the expected form of the subject sequence is a sequence of
            // letters and digits representing an integer with the radix
            // specified by base (C11 7.22.1.4/3)
            r = from_chars(s, s + sizeof(s), x);
            LIBCPP_ASSERT(r.ec == std::errc{});
            LIBCPP_ASSERT(r.ptr == s + 3);
            LIBCPP_ASSERT(x == 1);
        }

        {
            char s[] = "0X7BAtSGHDkEIXZg ";

            // The letters from a (or A) through z (or Z) are ascribed the
            // values 10 through 35; (C11 7.22.1.4/3)
            r = from_chars(s, s + sizeof(s), x, 36);
            LIBCPP_ASSERT(r.ec == std::errc::result_out_of_range);
            // The member ptr of the return value points to the first character
            // not matching the pattern
            LIBCPP_ASSERT(r.ptr == s + sizeof(s) - 2);
            LIBCPP_ASSERT(x == 1);

            // no "0x" or "0X" prefix shall appear if the value of base is 16
            r = from_chars(s, s + sizeof(s), x, 16);
            LIBCPP_ASSERT(r.ec == std::errc{});
            LIBCPP_ASSERT(r.ptr == s + 1);
            LIBCPP_ASSERT(x == 0);

            // only letters and digits whose ascribed values are less than that
            // of base are permitted. (C11 7.22.1.4/3)
            r = from_chars(s + 2, s + sizeof(s), x, 12);
            // If the parsed value is not in the range representable by the type
            // of value,
            if (!fits_in<T>(1150))
            {
                // value is unmodified and
                LIBCPP_ASSERT(x == 0);
                // the member ec of the return value is equal to
                // errc::result_out_of_range
                LIBCPP_ASSERT(r.ec == std::errc::result_out_of_range);
            }
            else
            {
                // Otherwise, value is set to the parsed value,
                LIBCPP_ASSERT(x == 1150);
                // and the member ec is value-initialized.
                LIBCPP_ASSERT(r.ec == std::errc{});
            }
            LIBCPP_ASSERT(r.ptr == s + 5);
        }
    }
};

template <typename T>
struct test_signed : roundtrip_test_base<T>
{
    using roundtrip_test_base<T>::test;

    void operator()()
    {
        test(-1);
        test(-12);
        test(-1, 10);
        test(-12, 10);
        test(-21734634, 10);
        test(-2647, 2);
        test(-0xcc1, 16);

        for (int b = 2; b < 37; ++b)
        {
            using xl = std::numeric_limits<T>;

            test(0, b);
            test(xl::lowest(), b);
            test((xl::max)(), b);
        }

        using std::from_chars;
        std::from_chars_result r;
        T x;

        {
            // If the pattern allows for an optional sign,
            char s[] = " - 9+12";
            // but the string has no digit characters following the sign,
            r = from_chars(s + 1, s + sizeof(s), x);
            // no characters match the pattern.
            LIBCPP_ASSERT(r.ptr == s + 1);
            LIBCPP_ASSERT(r.ec == std::errc::invalid_argument);

            // a minus sign is the only sign that may appear
            r = from_chars(s + 3, s + sizeof(s), x);
            LIBCPP_ASSERT(r.ec == std::errc{});
            // The member ptr of the return value points to the first character
            // not matching the pattern,
            LIBCPP_ASSERT(r.ptr == s + 4);
            LIBCPP_ASSERT(x == 9);

            r = from_chars(s + 5, s + 7, x);
            LIBCPP_ASSERT(r.ec == std::errc{});
            // or has the value last if all characters match.
            LIBCPP_ASSERT(r.ptr == s + 7);
            LIBCPP_ASSERT(x == 12);

            // If no characters match the pattern,
            r = from_chars(s + 4, s + sizeof(s), x);
            // value is unmodified,
            LIBCPP_ASSERT(x == 12);
            // the member ptr of the return value is first and
            LIBCPP_ASSERT(r.ptr == s + 4);
            // the member ec is equal to errc::invalid_argument.
            LIBCPP_ASSERT(r.ec == std::errc::invalid_argument);
        }
    }
};

int
main()
{
    run<test_basics>(integrals);
    run<test_signed>(all_signed);
}
