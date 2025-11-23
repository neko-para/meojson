#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <string>
#include <string_view>
#include <variant>

#include "forward.hpp"

namespace json
{

class value
{
    using array_ptr = std::unique_ptr<array>;
    using object_ptr = std::unique_ptr<object>;

public:
    enum class value_type : uint8_t
    {
        invalid,
        null,
        boolean,
        string,
        number,
        array,
        object
    };

    using var_t = std::variant<std::string, array_ptr, object_ptr>;

public:
    value();
    value(const value& rhs);
    value(value&& rhs) noexcept;
    ~value();

    value& operator=(const value& rhs);
    value& operator=(value&& rhs) noexcept;

    // null
    value(std::nullptr_t) noexcept;

    // bool
    value(bool val);

    // string
    value(const char* str);
    value(std::string str);
    value(std::string_view str);

    // number
    template <std::integral type_t>
    value(type_t num);
    template <std::floating_point type_t>
    value(type_t num);

    // array
    value(array arr);

    // object
    value(object obj);
    value(std::initializer_list<typename __impl::raw_object::value_type> list);

    // error
    value(char) = delete;
    value(wchar_t) = delete;
    value(char16_t) = delete;
    value(char32_t) = delete;

    // basic check
    bool valid() const noexcept;
    bool is_null() const noexcept;
    bool is_boolean() const noexcept;
    bool is_string() const noexcept;
    bool is_number() const noexcept;
    bool is_array() const noexcept;
    bool is_object() const noexcept;

    // basic convert
    bool as_boolean() const;
    std::string as_string() const;
    int as_integer() const;
    int as_int() const;
    unsigned as_unsigned() const;
    long as_long() const;
    unsigned long as_unsigned_long() const;
    long long as_long_long() const;
    unsigned long long as_unsigned_long_long() const;
    float as_float() const;
    double as_double() const;
    long double as_long_double() const;
    const array& as_array() const;
    const object& as_object() const;
    array& as_array();   // will convert null to array
    object& as_object(); // will convert null to object
    array take_array();
    object take_object();

private:
    static var_t deep_copy(const var_t& src);

    const std::string& as_basic_type_str() const;
    std::string& as_basic_type_str();

private:
    value_type _type = value_type::null;
    var_t _raw_data;
};

}
