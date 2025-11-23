#pragma once

#if __cplusplus < 202002L
#error "require c++20"
#endif

// IWYU pragma: begin_exports

#include "common/array.hpp"
#include "common/object.hpp"
#include "common/value.hpp"

// IWYU pragma: end_exports

#include "common/pri/array_impl.hpp"
#include "common/pri/object_impl.hpp"
#include "common/pri/value_impl.hpp"
