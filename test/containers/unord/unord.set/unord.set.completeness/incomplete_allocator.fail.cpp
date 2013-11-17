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

// Allocator shall satisfies the Allocator completeness requirements

#include <unordered_set>
#include "../../../empty_template_arguments.h"

struct X
{
    std::unordered_multiset
    <
        X,
        empty_hash<X>,
        empty_functor<X>,
        incomplete_allocator<X>
    > m;
};

int main()
{
}
