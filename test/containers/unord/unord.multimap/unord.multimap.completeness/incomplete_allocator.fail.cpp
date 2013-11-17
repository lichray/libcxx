//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <unordered_map>

// unordered_multimap

// Allocator shall satisfies the Allocator completeness requirements

#include <unordered_map>
#include "../../../empty_template_arguments.h"

struct X
{
    std::unordered_multimap
    <
        X,
        int,
        empty_hash<int>,
        empty_functor<int>,
        incomplete_allocator<std::pair<const X, int>>
    > m;
};

int main()
{
}
