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

// Container shall satisfies the Container completeness requirements

#include <stack>
#include "../../../empty_template_arguments.h"

struct X
{
    std::stack<X, incomplete_container<X>> q;
};

int main()
{
}
