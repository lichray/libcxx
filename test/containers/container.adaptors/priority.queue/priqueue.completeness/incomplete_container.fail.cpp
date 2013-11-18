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

// Container shall satisfies the Container completeness requirements

#include <queue>
#include "../../../empty_template_arguments.h"

struct X
{
    std::priority_queue<X, incomplete_container<X>> q;
};

int main()
{
}
