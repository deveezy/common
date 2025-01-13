#pragma once

/// @brief boost::uuids::uuid serializer to any format

#include <boost/uuid/uuid.hpp>
#include <string>

#include <formats/serialize/to.hpp>

namespace formats::serialize {

namespace detail {

std::string ToString(const boost::uuids::uuid &value);

}  // namespace detail

/// Outputs UUID in format: 12345678-1234-1234-1234-123412345678
template <typename Value>
Value Serialize(const boost::uuids::uuid &value, To<Value>) {
  return typename Value::Builder(detail::ToString(value)).ExtractValue();
}

template <typename StringBuilder>
void WriteToStream(const boost::uuids::uuid &value, StringBuilder &sw) {
  WriteToStream(detail::ToString(value), sw);
}

}  // namespace formats::serialize
