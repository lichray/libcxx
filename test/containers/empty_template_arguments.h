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

template <class T>
struct empty_functor
{
};

template <class T>
struct empty_hash
{
    std::size_t operator()(const T&) const _NOEXCEPT;
};

template <class T>
class incomplete_container
{
public:
    typedef T            value_type;
    typedef T&           reference;
    typedef const T&     const_reference;
    // missing `size_type` typedef
};

template <class T>
class empty_container
    : public incomplete_container<T>
{
public:
    typedef std::size_t  size_type;
};

#endif  // EMPTY_TEMPLATE_ARGUMENTS
