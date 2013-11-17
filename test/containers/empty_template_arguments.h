#ifndef EMPTY_TEMPLATE_ARGUMENTS
#define EMPTY_TEMPLATE_ARGUMENTS

#include <cstddef>

template <class T>
class empty_allocator
{
public:
    typedef T value_type;
};

template <class T>
class incomplete_allocator
{
    // missing `value_type` typedef
};

#endif  // EMPTY_TEMPLATE_ARGUMENTS
