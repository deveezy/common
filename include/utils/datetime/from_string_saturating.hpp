#pragma once

/// @brief Saturating converters from strings to time points.

#include <chrono>
#include <string>

namespace utils::datetime {

/// @brief Converts strings like "2012-12-12T00:00:00" to
/// std::chrono::system_clock::time_point in UTC timezone and saturates on
/// overflow
/// Example:
/// @snippet utils/datetime/from_string_saturating_test.cpp FromStringSaturation
std::chrono::system_clock::time_point FromRfc3339StringSaturating(const std::string &timestring);

/// @brief Converts strings of the specified format starting with "%Y" to
/// std::chrono::system_clock::time_point in UTC timezone and saturates on
/// overflow.
std::chrono::system_clock::time_point FromStringSaturating(const std::string &timestring, const std::string &format);

}  // namespace utils::datetime
