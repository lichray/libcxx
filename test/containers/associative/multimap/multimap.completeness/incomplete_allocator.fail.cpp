//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// multimap

// Allocator shall satisfies the Allocator completeness requirements

#include <map>
#include "../../../empty_template_arguments.h"

struct X
{
    std::multimap
    <
        X,
        int,
        empty_functor<X>,
        incomplete_allocator<std::pair<const X, int>>
    > m;
};

int main()
{
}
