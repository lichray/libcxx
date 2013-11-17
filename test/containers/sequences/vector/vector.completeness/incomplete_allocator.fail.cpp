//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <vector>

// vector

// Allocator shall satisfies the Allocator completeness requirements

#include <vector>
#include "../../../empty_template_arguments.h"

struct X
{
    std::vector<X, incomplete_allocator<X>> v;
};

int main()
{
}
