//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <unordered_set>

// unordered_set

// Hash shall satisfies the Hash completeness requirements

#include <unordered_set>

struct X
{
    std::unordered_set<X> m;
};

int main()
{
}
