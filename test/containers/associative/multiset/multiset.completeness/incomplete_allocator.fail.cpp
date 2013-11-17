//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <multiset>

// multiset

// Allocator shall satisfies the Allocator completeness requirements

#include <set>
#include "../../../empty_template_arguments.h"

struct X
{
    std::multiset
    <
        X,
        empty_functor<X>,
        incomplete_allocator<X>
    > m;
};

int main()
{
}
