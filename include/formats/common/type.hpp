#pragma once

/// @brief @copybrief formats::common::Type

/// Common utilities for all the formats
namespace formats::common {

/// Common enum of types
enum class Type {
  kNull,    /// Value or ValueBuilder holds Null value
  kArray,   /// Value or ValueBuilder holds an Array
  kObject,  /// Value or ValueBuilder holds a Map
};

}  // namespace formats::common
