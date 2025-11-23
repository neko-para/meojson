#pragma once

#include "../array.hpp"

#include "../object.hpp"
#include "../value.hpp"
#include "utils.hpp"

namespace json
{

inline array::array() = default;

inline array::array(const array& rhs) = default;

inline array::array(array&& rhs) noexcept = default;

inline array::~array() = default;

inline array& array::operator=(const array& rhs) = default;

inline array& array::operator=(array&& rhs) noexcept = default;

inline array::array(raw_array::size_type size)
    : _array_data(size)
{
}

inline array::array(std::initializer_list<value_type> list)
    : _array_data(std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()))
{
}

// manipulate

inline bool array::empty() const noexcept
{
    return _array_data.empty();
}

inline array::raw_array::size_type array::size() const noexcept
{
    return _array_data.size();
}

}
