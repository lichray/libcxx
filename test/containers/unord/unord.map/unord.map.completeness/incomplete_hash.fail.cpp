//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <unordered_map>

// unordered_map

// Hash shall satisfies the Hash completeness requirements

#include <unordered_map>

struct X
{
    std::unordered_map<X, int> m;
};

int main()
{
}
