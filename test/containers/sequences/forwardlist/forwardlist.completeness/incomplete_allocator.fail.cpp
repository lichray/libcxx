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

// Allocator shall satisfies the Allocator completeness requirements

#include <forward_list>
#include "../../../empty_template_arguments.h"

struct X
{
    std::forward_list<X, incomplete_allocator<X>> l;
};

int main()
{
}
