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

// multimap<Incomplete, Incomplete>

#include <map>
#include "../../../empty_template_arguments.h"

struct X
{
    std::multimap<int, X> m1;
    std::multimap<X, int> m2;
    std::multimap
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
