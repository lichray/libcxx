//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <queue>

// queue

// queue<Incomplete>

#include <queue>
#include "../../../empty_template_arguments.h"

struct X
{
    std::queue<X> q1;
    std::queue<X, std::deque<X, empty_allocator<X>>> q2;
};

int main()
{
}
