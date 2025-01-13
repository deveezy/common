#pragma once

/// @brief @copybrief formats::common::ValidateFloat()

#include <cmath>

#include <utils/assert.hpp>

namespace formats::common {

/// @brief Common restrictions to floating type values serialization. Asserts
/// or throws on NaN and Inf values.
template <typename ExceptionType, typename Float>
Float ValidateFloat(Float value) {
  if (std::isnan(value)) {
    ASSERT_MSG(false, "Floating point nan value serialization is forbidden");
    throw ExceptionType("Floating point nan value serialization is forbidden");
  }
  if (std::isinf(value)) {
    ASSERT_MSG(false, "Floating point inf value serialization is forbidden");
    throw ExceptionType("Floating point inf value serialization is forbidden");
  }
  return value;
}

}  // namespace formats::common
