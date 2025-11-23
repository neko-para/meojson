#pragma once

#include "forward.hpp"

namespace json
{

class object
{
    friend class value;
    friend class array;

public:
    using raw_object = __impl::raw_object;
    using key_type = typename raw_object::key_type;
    using mapped_type = typename raw_object::mapped_type;
    using value_type = typename raw_object::value_type;
    using iterator = typename raw_object::iterator;
    using const_iterator = typename raw_object::const_iterator;

public:
    object();
    object(const object& rhs);
    object(object&& rhs) noexcept;
    ~object();

    object& operator=(const object& rhs);
    object& operator=(object&& rhs) noexcept;

    object(std::initializer_list<value_type> list);

    // manipulate
    bool empty() const noexcept;
    raw_object::size_type size() const noexcept;

private:
    raw_object _object_data;
};

}
