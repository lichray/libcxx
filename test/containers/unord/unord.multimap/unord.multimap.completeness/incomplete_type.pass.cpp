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

// unordered_multimap<Incomplete, Incomplete>

#include <unordered_map>
#include "../../../empty_template_arguments.h"

struct X
{
    std::unordered_multimap<int, X> m1;
    std::unordered_multimap<X, int, empty_hash<X>> m2;
    std::unordered_multimap
    <
        X,
        int,
        empty_hash<X>,
        empty_functor<X>,
        empty_allocator<std::pair<const X, int>>
    > m3;
};

int main()
{
}
