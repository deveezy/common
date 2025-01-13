#pragma once

/// @brief Serializers for std::variant

#include <variant>

#include <formats/serialize/to.hpp>

namespace formats::serialize {

template <typename Value, typename... Types>
Value Serialize(const std::variant<Types...> &value, To<Value>) {
  return std::visit([](const auto &item) { return typename Value::Builder(item).ExtractValue(); }, value);
}

}  // namespace formats::serialize
