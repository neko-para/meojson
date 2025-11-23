#pragma once

#include "forward.hpp"

namespace json
{

class array
{
    friend class value;
    friend class object;

public:
    using raw_array = __impl::raw_array;
    using value_type = typename raw_array::value_type;
    using iterator = typename raw_array::iterator;
    using const_iterator = typename raw_array::const_iterator;
    using reverse_iterator = typename raw_array::reverse_iterator;
    using const_reverse_iterator = typename raw_array::const_reverse_iterator;

public:
    array();
    array(const array& rhs);
    array(array&& rhs) noexcept;
    ~array();

    array& operator=(const array& rhs);
    array& operator=(array&& rhs) noexcept;

    array(raw_array::size_type size);
    array(std::initializer_list<value_type> list);

    // manipulate
    bool empty() const noexcept;
    raw_array::size_type size() const noexcept;

private:
    raw_array _array_data;
};

}
