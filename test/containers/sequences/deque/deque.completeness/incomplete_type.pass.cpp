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

// deque<Incomplete>

#include <deque>
#include "../../../empty_template_arguments.h"

struct X
{
    std::deque<X> q1;
    std::deque<X, empty_allocator<X>> q2;
};

int main()
{
}
