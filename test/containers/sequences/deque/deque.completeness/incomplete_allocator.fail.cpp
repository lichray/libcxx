//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <deque>

// deque

// Allocator shall satisfies the Allocator completeness requirements

#include <deque>
#include "../../../empty_template_arguments.h"

struct X
{
    std::deque<X, incomplete_allocator<X>> q;
};

int main()
{
}
