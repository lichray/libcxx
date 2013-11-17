//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <map>

// map

// map<Incomplete, Incomplete>

#include <map>
#include "../../../empty_template_arguments.h"

struct X
{
    std::map<int, X> m1;
    std::map<X, int> m2;
    std::map
    <
        X,
        int,
        empty_functor<X>,
        empty_allocator<std::pair<const X, int>>
    > m3;
};

int main()
{
}
