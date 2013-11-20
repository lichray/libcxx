//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <iterator>

// insert_iterator

// insert_iterator<Incomplete>

#include <iterator>
#include <vector>

struct X
{
    // Requires Container::iterator to be complete in addition to
    // the Container's completeness.
    std::insert_iterator<std::vector<X>> it;
};

int main()
{
}
