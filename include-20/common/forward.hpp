#pragma once

#include <map>
#include <string>
#include <vector>

namespace json
{

class value;
class array;
class object;

namespace __impl
{

using raw_array = std::vector<value>;
using raw_object = std::map<std::string, value>;

}

}
