//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <queue>

// priority_queue

// priority_queue<Incomplete>

#include <queue>
#include "../../../empty_template_arguments.h"

struct X
{
    std::priority_queue<X> q1;
    std::priority_queue
    <
        X,
        std::vector<X, empty_allocator<X>>,
        empty_functor<X>
    > q2;
    std::priority_queue<X, empty_container<X>> q3;
};

int main()
{
}
