#pragma once

/// @file userver/formats/serialize/common_containers.hpp
/// @brief Serializers for standard containers and optional
/// @ingroup userver_universal userver_formats_serialize

#include <optional>
#include <type_traits>

#include <formats/common/type.hpp>
#include <formats/serialize/to.hpp>
#include <utils/meta.hpp>

namespace boost::uuids {
struct uuid;
}

namespace utils::impl::strong_typedef {
struct StrongTypedefTag;
}

/// Common serializers
namespace formats::serialize {

/// Common containers serialization (vector/set)
template <typename T, typename Value>
Value Serialize(const T &value, To<Value>)
  requires(meta::kIsRange<T> && !meta::kIsMap<T> && !std::is_same_v<T, boost::uuids::uuid> &&
           !std::is_convertible_v<T &, utils::impl::strong_typedef::StrongTypedefTag &>)
{
  typename Value::Builder builder(formats::common::Type::kArray);
  for (const auto &item : value) {
    // explicit cast for vector<bool> shenanigans
    builder.PushBack(static_cast<const meta::RangeValueType<T> &>(item));
  }
  return builder.ExtractValue();
}

/// Mappings serialization
template <typename T, typename Value>
Value Serialize(const T &value, To<Value>)
  requires(meta::kIsUniqueMap<T>)
{
  typename Value::Builder builder(formats::common::Type::kObject);
  for (const auto &[key, value] : value) { builder[key] = value; }
  return builder.ExtractValue();
}

/// std::optional serialization
template <typename T, typename Value>
Value Serialize(const std::optional<T> &value, To<Value>) {
  if (!value) return {};

  return typename Value::Builder(*value).ExtractValue();
}

}  // namespace formats::serialize
