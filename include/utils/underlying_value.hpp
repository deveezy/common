#pragma once

/// @file userver/utils/underlying_value.hpp
/// @brief @copybrief utils::UnderlyingValue
/// @ingroup userver_universal

#include <type_traits>

namespace utils {

/// @brief Function that extracts integral value from enum or StrongTypedef
template <class T>
constexpr auto UnderlyingValue(T v) noexcept
  requires(std::is_enum_v<T>)
{
  return static_cast<std::underlying_type_t<T>>(v);
}

}  // namespace utils
