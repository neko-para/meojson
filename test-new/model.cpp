#include <cassert>
#include <utility>

#include "json.hpp"

using namespace json;

static void test_value()
{
    value v_g0;
    array a_g0;
    object o_g0;

    value v_copy_0 = v_g0;
    value v_copy_1 = a_g0;
    value v_copy_2 = o_g0;
    value v_move_0 = std::move(v_g0);
    value v_move_1 = std::move(a_g0);
    value v_move_2 = std::move(o_g0);

    v_copy_0 = v_g0;
    v_copy_1 = a_g0;
    v_copy_2 = o_g0;
    v_move_0 = std::move(v_g0);
    v_move_1 = std::move(a_g0);
    v_move_2 = std::move(o_g0);

    value v_n0(nullptr);

    value v_b0(false);
    value v_b1(true);

    value v_s0("123");
    std::string s = "123";
    value v_s1(s);
    std::string_view sv = "123";
    value v_s2(sv);

    value v_i0(123);
    value v_f0(123.456);

    array arr = { 1, 2, 3 };
    value v_a0(arr);

    object obj = { { "key", 0 } };
    value v_o0(obj);
    value v_o1(
        {
            { "key_n", nullptr },
            { "key_b", false },
            { "key_i", 0 },
            { "key_f", 0.0 },
            {
                "key_o",
                { { "subk", 0 } },
            },
            {
                "key_a",
                array { 0 },
            },
        });

    static_assert(!std::is_constructible_v<value, char>, "char shall not construct a value");
    static_assert(!std::is_constructible_v<value, wchar_t>, "wchar_t shall not construct a value");
    static_assert(!std::is_constructible_v<value, char16_t>, "char16_t shall not construct a value");
    static_assert(!std::is_constructible_v<value, char32_t>, "char32_t shall not construct a value");

    assert(v_n0.is_null());
    assert(v_b0.is_boolean());
    assert(v_b1.is_boolean());
    assert(v_s0.is_string());
    assert(v_s1.is_string());
    assert(v_s2.is_string());
    assert(v_i0.is_number());
    assert(v_f0.is_number());
    assert(v_a0.is_array());
    assert(v_o0.is_object());
    assert(v_o1.is_object());

    assert(v_b0.as_boolean() == false);
    assert(v_b1.as_boolean() == true);
    assert(v_s0.as_string() == "123");
    assert(v_s1.as_string() == "123");
    assert(v_s2.as_string() == "123");
    assert(v_i0.as_int() == 123);
    assert(v_i0.as_unsigned() == 123u);
    assert(v_i0.as_long() == 123l);
    assert(v_i0.as_unsigned_long() == 123ul);
    assert(v_i0.as_long_long() == 123ll);
    assert(v_i0.as_unsigned_long_long() == 123ull);
    assert(v_f0.as_float() == 123.456f);
    assert(v_f0.as_double() == 123.456);
    assert(v_f0.as_long_double() == 123.456L);
    assert(v_a0.as_array().size() == 3);
    assert(static_cast<const value&>(v_a0).as_array().size() == 3);
    assert(v_a0.take_array().size() == 3);
    assert(v_o0.as_object().size() == 1);
    assert(static_cast<const value&>(v_o0).as_object().size() == 1);
    assert(v_o0.take_object().size() == 1);
    assert(v_o1.as_object().size() == 6);
    assert(static_cast<const value&>(v_o1).as_object().size() == 6);
    assert(v_o1.take_object().size() == 6);
}

static void test_array()
{
    array a_g0;

    array a_copy_0 = a_g0;
    array a_move_0 = std::move(a_g0);

    a_copy_0 = a_g0;
    a_move_0 = std::move(a_g0);

    array a_count(1);
    array a_list(
        {
            0,
            "123",
        });
}

static void test_object()
{
    object o_g0;

    object o_copy_0 = o_g0;
    object o_move_0 = std::move(o_g0);

    o_copy_0 = o_g0;
    o_move_0 = std::move(o_g0);

    object o_list(
        {
            { "key", 0 },
        });
}

void test_model()
{
    test_value();
    test_array();
    test_object();
}
