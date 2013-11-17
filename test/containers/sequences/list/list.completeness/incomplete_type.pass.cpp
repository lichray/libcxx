//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <list>

// list

// list<Incomplete>

#include <list>
#include "../../../empty_template_arguments.h"

struct X
{
    std::list<X> l1;
    std::list<X, empty_allocator<X>> l2;
};

int main()
{
}
