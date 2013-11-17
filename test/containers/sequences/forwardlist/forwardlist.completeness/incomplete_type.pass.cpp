//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <forward_list>

// forward_list

// forward_list<Incomplete>

#include <forward_list>
#include "../../../empty_template_arguments.h"

struct X
{
    std::forward_list<X> v1;
    std::forward_list<X, empty_allocator<X>> v2;
};

int main()
{
}
