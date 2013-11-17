//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <set>

// set

// set<Incomplete>

#include <set>
#include "../../../empty_template_arguments.h"

struct X
{
    std::set<X> m1;
    std::set
    <
        X,
        empty_functor<X>,
        empty_allocator<X>
    > m2;
};

int main()
{
}
