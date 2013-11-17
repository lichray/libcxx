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

// Allocator shall satisfies the Allocator completeness requirements

#include <list>
#include "../../../empty_template_arguments.h"

struct X
{
    std::list<X, incomplete_allocator<X>> l;
};

int main()
{
}
