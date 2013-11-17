//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <stack>

// stack

// stack<Incomplete>

#include <stack>
#include "../../../empty_template_arguments.h"

struct X
{
    std::stack<X> q1;
    std::stack<X, std::deque<X, empty_allocator<X>>> q2;
};

int main()
{
}
