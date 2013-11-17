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

// unordered_set<Incomplete>

#include <unordered_set>
#include "../../../empty_template_arguments.h"

struct X
{
    std::unordered_set<X, empty_hash<X>> m1;
    std::unordered_set
    <
        X,
        empty_hash<X>,
        empty_functor<X>,
        empty_allocator<X>
    > m2;
};

int main()
{
}
