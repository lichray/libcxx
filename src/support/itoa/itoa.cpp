// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <support/itoa/itoa.h>
#include <string.h>

_LIBCPP_BEGIN_NAMESPACE_STD

namespace __itoa
{

static const char cDigitsLut[200] = {
    '0', '0', '0', '1', '0', '2', '0', '3', '0', '4', '0', '5', '0', '6', '0',
    '7', '0', '8', '0', '9', '1', '0', '1', '1', '1', '2', '1', '3', '1', '4',
    '1', '5', '1', '6', '1', '7', '1', '8', '1', '9', '2', '0', '2', '1', '2',
    '2', '2', '3', '2', '4', '2', '5', '2', '6', '2', '7', '2', '8', '2', '9',
    '3', '0', '3', '1', '3', '2', '3', '3', '3', '4', '3', '5', '3', '6', '3',
    '7', '3', '8', '3', '9', '4', '0', '4', '1', '4', '2', '4', '3', '4', '4',
    '4', '5', '4', '6', '4', '7', '4', '8', '4', '9', '5', '0', '5', '1', '5',
    '2', '5', '3', '5', '4', '5', '5', '5', '6', '5', '7', '5', '8', '5', '9',
    '6', '0', '6', '1', '6', '2', '6', '3', '6', '4', '6', '5', '6', '6', '6',
    '7', '6', '8', '6', '9', '7', '0', '7', '1', '7', '2', '7', '3', '7', '4',
    '7', '5', '7', '6', '7', '7', '7', '8', '7', '9', '8', '0', '8', '1', '8',
    '2', '8', '3', '8', '4', '8', '5', '8', '6', '8', '7', '8', '8', '8', '9',
    '9', '0', '9', '1', '9', '2', '9', '3', '9', '4', '9', '5', '9', '6', '9',
    '7', '9', '8', '9', '9'};

#define APPEND1(i)                              \
    do                                          \
    {                                           \
        *buffer++ = '0' + static_cast<char>(i); \
    } while (0)

#define APPEND2(i)                             \
    do                                         \
    {                                          \
        memcpy(buffer, &cDigitsLut[(i)*2], 2); \
        buffer += 2;                           \
    } while (0)

#define APPEND3(i)          \
    do                      \
    {                       \
        APPEND1((i) / 100); \
        APPEND2((i) % 100); \
    } while (0)

#define APPEND4(i)          \
    do                      \
    {                       \
        APPEND2((i) / 100); \
        APPEND2((i) % 100); \
    } while (0)

char*
__u32toa(uint32_t value, char* buffer)
{
    if (value < 10000)
    {
        if (value < 100)
        {
            if (value < 10)
                APPEND1(value);
            else
                APPEND2(value);
        }
        else
        {
            if (value < 1000)
                APPEND3(value);
            else
                APPEND4(value);
        }
    }
    else if (value < 100000000)
    {
        // value = bbbbcccc
        const uint32_t b = value / 10000;
        const uint32_t c = value % 10000;

        if (value < 1000000)
        {
            if (value < 100000)
                APPEND1(b);
            else
                APPEND2(b);
        }
        else
        {
            if (value < 10000000)
                APPEND3(b);
            else
                APPEND4(b);
        }

        APPEND4(c);
    }
    else
    {
        // value = aabbbbcccc in decimal
        const uint32_t a = value / 100000000;  // 1 to 42
        value %= 100000000;

        if (a < 10)
            APPEND1(a);
        else
            APPEND2(a);

        APPEND4(value / 10000);
        APPEND4(value % 10000);
    }

    return buffer;
}

char*
__u64toa(uint64_t value, char* buffer)
{
    if (value < 100000000)
    {
        uint32_t v = static_cast<uint32_t>(value);
        if (v < 10000)
        {
            if (v < 100)
            {
                if (v < 10)
                    APPEND1(v);
                else
                    APPEND2(v);
            }
            else
            {
                if (v < 1000)
                    APPEND3(v);
                else
                    APPEND4(v);
            }
        }
        else
        {
            // value = bbbbcccc
            const uint32_t b = v / 10000;
            const uint32_t c = v % 10000;

            if (v < 1000000)
            {
                if (v < 100000)
                    APPEND1(b);
                else
                    APPEND2(b);
            }
            else
            {
                if (v < 10000000)
                    APPEND3(b);
                else
                    APPEND4(b);
            }

            APPEND4(c);
        }
    }
    else if (value < 10000000000000000)
    {
        const uint32_t v0 = static_cast<uint32_t>(value / 100000000);
        const uint32_t v1 = static_cast<uint32_t>(value % 100000000);

        const uint32_t b0 = v0 / 10000;
        const uint32_t c0 = v0 % 10000;

        if (v0 < 1000000)
        {
            if (v0 < 100000)
                APPEND1(b0);
            else
                APPEND2(b0);
        }
        else
        {
            if (v0 < 10000000)
                APPEND3(b0);
            else
                APPEND4(b0);
        }

        APPEND4(c0);
        APPEND4(v1 / 10000);
        APPEND4(v1 % 10000);
    }
    else
    {
        const uint32_t a =
            static_cast<uint32_t>(value / 10000000000000000);  // 1 to 1844
        value %= 10000000000000000;

        if (a < 100)
        {
            if (a < 10)
                APPEND1(a);
            else
                APPEND2(a);
        }
        else
        {
            if (a < 1000)
                APPEND3(a);
            else
                APPEND4(a);
        }

        const uint32_t v0 = static_cast<uint32_t>(value / 100000000);
        const uint32_t v1 = static_cast<uint32_t>(value % 100000000);
        APPEND4(v0 / 10000);
        APPEND4(v0 % 10000);
        APPEND4(v1 / 10000);
        APPEND4(v1 % 10000);
    }

    return buffer;
}

}  // namespace __itoa

_LIBCPP_END_NAMESPACE_STD
