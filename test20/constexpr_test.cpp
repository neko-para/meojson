#include <array>
#include <iostream>

#include "json.hpp"

using namespace json::literals;

// constexpr json::object wrap_obj(json::value v)
// {
//     return json::object { { "kkk", v } };
// }

// constexpr json::value empty;
// constexpr json::object wempty = wrap_obj(empty);

constexpr std::string test()
{
    auto empty = "{ \"abc\": 1 }"_cjobject;
    constexpr auto obj2 = json::cparse("{ \"axxbc\": {} }").value().to_string().size();
    // json::cobject empty = { { "abc", 1 } };

    empty["def"] = obj2;
    empty["float"] = -1234.567890987654321;
    empty["float2"] = 0.00012345678998765;
    empty["float3"] = 123456789876543211234.;
    empty.emplace("float", 1);

    auto test1 = "{ \"k1\": 2 }"_cjobject;
    auto test2 = json::cobject { { "k1", 2 } };
    if (test1 == test2) {
        return empty.to_string();
    } else {
        return "error!";
    }
}

constexpr size_t get_size()
{
    auto str = test();
    return str.size();
}

template <size_t N>
constexpr std::array<char, N + 1> get_data()
{
    auto str = test();
    std::array<char, N + 1> result;
    std::copy(str.begin(), str.end(), result.begin());
    result[N] = 0;
    return result;
}

int main()
{
    constexpr auto size = get_size();
    constexpr auto arr = get_data<size>();
    std::cout << arr.data() << std::endl;
}
