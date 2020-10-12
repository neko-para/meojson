#pragma once

#include <string>
#include <regex>

namespace json
{
    class value;
    class object;
    class array;

    class parser
    {
    public:
        parser() = delete;
        ~parser() = default;

        static value parse(const std::string &content);

    private:
        static const std::string reg_str_json_whitespace;

        static const std::string reg_str_json_null;
        static const std::string reg_str_json_boolean;
        static const std::string reg_str_json_string;
        static const std::string reg_str_json_number_fraction;
        static const std::string reg_str_json_number_exponent;
        static const std::string reg_str_json_number;

        static const std::string reg_str_json_non_nested_value;

        static const std::regex reg_json_null;
        static const std::regex reg_json_boolean;
        static const std::regex reg_json_string;
        static const std::regex reg_json_number;
        static const std::regex reg_json_non_nested_value;

        static value parse_value(const std::string &content, std::string::const_iterator &cur);
        static object parse_object(const std::string &content, std::string::const_iterator &cur);
        static array parse_array(const std::string &content, std::string::const_iterator &cur);
        static void parse_whitespace(const std::string &content, std::string::const_iterator &cur);
    };
} // namespace json