#pragma once

/// @file userver/formats/parse/boost_optional.hpp
/// @brief Parsers and converters for boost::optional
/// @ingroup userver_universal userver_formats_parse

#include <formats/parse/to.hpp>

#include <optional>

namespace formats::parse {

template <class Value, typename T>
std::optional<T> Parse(const Value &value, To<std::optional<T>>) {
  if (value.IsMissing() || value.IsNull()) { return std::nullopt; }
  return value.template As<T>();
}

template <class Value>
std::optional<std::nullptr_t> Parse(const Value &, To<std::optional<std::nullptr_t>>) {
  static_assert(!sizeof(Value), "optional<nullptr_t> is forbidden, check IsNull() instead");
  return nullptr;
}

template <class Value, typename T>
std::optional<T> Convert(const Value &value, To<std::optional<T>>) {
  if (value.IsMissing() || value.IsNull()) { return std::nullopt; }
  return value.template ConvertTo<T>();
}

template <class Value>
std::optional<std::nullptr_t> Convert(const Value &, To<std::optional<std::nullptr_t>>) {
  static_assert(!sizeof(Value), "optional<nullptr_t> is forbidden, check IsNull() instead");
  return nullptr;
}

}  // namespace formats::parse
