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

// vector<Incomplete>

#include <vector>
#include "../../../empty_template_arguments.h"

struct X
{
    std::vector<X> v1;
    std::vector<X, empty_allocator<X>> v2;
};

int main()
{
}
