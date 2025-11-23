#pragma once

#include <iomanip>
#include <sstream>
#include <string>

namespace json::__impl
{

inline std::string true_string()
{
    return { 't', 'r', 'u', 'e' };
}

inline std::string false_string()
{
    return { 'f', 'a', 'l', 's', 'e' };
}

inline std::string null_string()
{
    return { 'n', 'u', 'l', 'l' };
}

template <std::integral type_t>
inline std::string to_string(type_t num)
{
    return std::to_string(num);
}

template <std::floating_point type_t>
inline std::string to_string(type_t num)
{
#ifdef MEOJSON_KEEP_FLOATING_PRECISION
    std::ostringstream oss;
    oss << std::setprecision(std::numeric_limits<type_t>::max_digits10) << num;
    return oss.str();
#endif
    return std::to_string(num);
}

}
