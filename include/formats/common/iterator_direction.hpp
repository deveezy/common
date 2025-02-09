#pragma once

namespace formats::common {

/// @brief Helper to distinguish forward and reverse iterators for Value
enum class IteratorDirection {
  kForward = 1,
  kReverse = -1,
};

}  // namespace formats::common
