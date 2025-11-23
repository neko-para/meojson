#pragma once

#include "../object.hpp"

#include "../array.hpp"
#include "../value.hpp"
#include "utils.hpp"

namespace json
{

inline object::object() = default;

inline object::object(const object& rhs) = default;

inline object::object(object&& rhs) noexcept = default;

inline object::~object() = default;

inline object& object::operator=(const object& rhs) = default;

inline object& object::operator=(object&& rhs) noexcept = default;

inline object::object(std::initializer_list<value_type> list)
    : _object_data(std::make_move_iterator(list.begin()), std::make_move_iterator(list.end()))
{
}

// manipulate

inline bool object::empty() const noexcept
{
    return _object_data.empty();
}

inline object::raw_object::size_type object::size() const noexcept
{
    return _object_data.size();
}

}
