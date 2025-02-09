#pragma once

/// @brief @copybrief utils::StringToDuration

#include <chrono>
#include <string>

namespace utils {

/// @brief Converts strings like "10s", "5d", "1h" to durations
///
/// Understands the following suffixes:
///   s   - seconds
///   ms  - milliseconds
///   m   - minutes
///   h   - hours
///   d   - days
std::chrono::milliseconds StringToDuration(const std::string &data);

}  // namespace utils
