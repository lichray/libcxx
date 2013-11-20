//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <iterator>

// front_insert_iterator

// front_insert_iterator<Incomplete>

#include <iterator>
#include "../../../../containers/empty_template_arguments.h"

struct X
{
    std::front_insert_iterator<empty_container<X>> it;
};

int main()
{
}
