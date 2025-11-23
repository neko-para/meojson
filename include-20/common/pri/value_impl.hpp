#pragma once

#include "../value.hpp"

#include "../array.hpp"
#include "../exception.hpp"
#include "../object.hpp"
#include "utils.hpp"

namespace json
{

inline value::value() = default;

inline value::value(const value& rhs)
    : _type(rhs._type)
    , _raw_data()
{
}

inline value::value(value&& rhs) noexcept = default;

inline value::~value() = default;

inline value& value::operator=(const value& rhs)
{
    if (&rhs == this) {
        return *this;
    }

    _type = rhs._type;
    _raw_data = deep_copy(rhs._raw_data);

    return *this;
}

inline value& value::operator=(value&& rhs) noexcept = default;

// null

inline value::value(nullptr_t) noexcept
    : _type(value_type::null)
{
}

// bool

inline value::value(bool val)
    : _type(value_type::boolean)
    , _raw_data(val ? __impl::true_string() : __impl::false_string()) {};

// string

inline value::value(const char* str)
    : _type(value_type::string)
    , _raw_data(std::string(str))
{
}

inline value::value(std::string str)
    : _type(value_type::string)
    , _raw_data(std::move(str))
{
}

inline value::value(std::string_view str)
    : _type(value_type::string)
    , _raw_data(std::string(str))
{
}

// number

template <std::integral type_t>
inline value::value(type_t num)
    : _type(value_type::number)
    , _raw_data(__impl::to_string(num))
{
}

template <std::floating_point type_t>
inline value::value(type_t num)
    : _type(value_type::number)
    , _raw_data(__impl::to_string(num))
{
}

// array
inline value::value(array arr)
    : _type(value_type::array)
    , _raw_data(std::make_unique<array>(std::move(arr)))
{
}

// object
inline value::value(object obj)
    : _type(value_type::object)
    , _raw_data(std::make_unique<object>(std::move(obj)))
{
}

inline value::value(std::initializer_list<typename __impl::raw_object::value_type> list)
    : _type(value_type::object)
    , _raw_data(std::make_unique<object>(list))
{
}

// basic check

inline bool value::valid() const noexcept
{
    return _type != value_type::invalid;
}

inline bool value::is_null() const noexcept
{
    return _type == value_type::null;
}

inline bool value::is_boolean() const noexcept
{
    return _type == value_type::boolean;
}

inline bool value::is_string() const noexcept
{
    return _type == value_type::string;
}

inline bool value::is_number() const noexcept
{
    return _type == value_type::number;
}

inline bool value::is_array() const noexcept
{
    return _type == value_type::array;
}

inline bool value::is_object() const noexcept
{
    return _type == value_type::object;
}

// basic convert

inline bool value::as_boolean() const
{
    if (is_boolean()) {
        if (const std::string& b_str = as_basic_type_str(); b_str == __impl::true_string()) {
            return true;
        }
        else if (b_str == __impl::false_string()) {
            return false;
        }
        else {
            throw exception("Unknown Parse Error");
        }
    }
    else {
        throw exception("Wrong Type");
    }
}

inline std::string value::as_string() const
{
    if (is_string()) {
        return as_basic_type_str();
    }
    else {
        throw exception("Wrong Type");
    }
}

inline int value::as_integer() const
{
    return as_int();
}

inline int value::as_int() const
{
    if (is_number()) {
        return std::stoi(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline unsigned value::as_unsigned() const
{
    return static_cast<unsigned>(as_unsigned_long());
}

inline long value::as_long() const
{
    if (is_number()) {
        return std::stol(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline unsigned long value::as_unsigned_long() const
{
    if (is_number()) {
        return std::stoul(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline long long value::as_long_long() const
{
    if (is_number()) {
        return std::stoll(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline unsigned long long value::as_unsigned_long_long() const
{
    if (is_number()) {
        return std::stoull(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline float value::as_float() const
{
    if (is_number()) {
        return std::stof(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline double value::as_double() const
{
    if (is_number()) {
        return std::stod(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline long double value::as_long_double() const
{
    if (is_number()) {
        return std::stold(as_basic_type_str());
    }
    else {
        throw exception("Wrong Type");
    }
}

inline const array& value::as_array() const
{
    if (is_array()) {
        return *std::get<array_ptr>(_raw_data);
    }

    throw exception("Wrong Type");
}

inline const object& value::as_object() const
{
    if (is_object()) {
        return *std::get<object_ptr>(_raw_data);
    }

    throw exception("Wrong Type");
}

inline array& value::as_array()
{
    if (is_null()) {
        *this = array {};
    }

    if (is_array()) {
        return *std::get<array_ptr>(_raw_data);
    }

    throw exception("Wrong Type");
}

inline object& value::as_object()
{
    if (is_null()) {
        *this = object {};
    }

    if (is_object()) {
        return *std::get<object_ptr>(_raw_data);
    }

    throw exception("Wrong Type");
}

inline array value::take_array()
{
    if (is_array()) {
        return std::move(*std::get<array_ptr>(_raw_data));
    }

    throw exception("Wrong Type");
}

inline object value::take_object()
{
    if (is_object()) {
        return std::move(*std::get<object_ptr>(_raw_data));
    }

    throw exception("Wrong Type");
}

// private

inline value::var_t value::deep_copy(const var_t& src)
{
    var_t dst;
    if (const auto string_ptr = std::get_if<std::string>(&src)) {
        dst = *string_ptr;
    }
    else if (const auto arr_ptr = std::get_if<array_ptr>(&src)) {
        dst = std::make_unique<array>(**arr_ptr);
    }
    else if (const auto obj_ptr = std::get_if<object_ptr>(&src)) {
        dst = std::make_unique<object>(**obj_ptr);
    }
    else {
        // maybe invalid_value
    }

    return dst;
}

inline const std::string& value::as_basic_type_str() const
{
    return std::get<std::string>(_raw_data);
}

inline std::string& value::as_basic_type_str()
{
    return std::get<std::string>(_raw_data);
}

}
