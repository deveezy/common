#pragma once

/// @brief @copybrief utils::FromString

#include <cctype>
#include <cerrno>
#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <string_view>
#include <type_traits>
#include <typeindex>

#include <utils/meta_light.hpp>

namespace utils {

namespace impl {

[[noreturn]] void ThrowFromStringException(
    std::string_view message, std::string_view input, std::type_index resultType);

template <typename T>
T FromString(const char *str)
  requires(std::is_floating_point_v<T>)
{
  static_assert(!std::is_const_v<T> && !std::is_volatile_v<T>);
  static_assert(!std::is_reference_v<T>);

  if (str == nullptr) { impl::ThrowFromStringException("nullptr string", "<null>", typeid(T)); }
  if (str[0] == '\0') { impl::ThrowFromStringException("empty string", str, typeid(T)); }
  if (std::isspace(str[0])) { impl::ThrowFromStringException("leading spaces are not allowed", str, typeid(T)); }

  errno     = 0;
  char *end = nullptr;

  const auto result = [&] {
    if constexpr (std::is_same_v<T, float>) {
      return std::strtof(str, &end);
    } else if constexpr (std::is_same_v<T, double>) {
      return std::strtod(str, &end);
    } else if constexpr (std::is_same_v<T, long double>) {
      return std::strtold(str, &end);
    }
  }();

  if (errno == ERANGE && !(result < 1 && result > 0.0)) { impl::ThrowFromStringException("overflow", str, typeid(T)); }

  if (end == str) { impl::ThrowFromStringException("no number found", str, typeid(T)); }

  if (*end != '\0') {
    if (std::isspace(*end)) {
      impl::ThrowFromStringException("trailing spaces are not allowed", str, typeid(T));
    } else {
      impl::ThrowFromStringException("extra junk at the end of the string is not allowed", str, typeid(T));
    }
  }

  return result;
}

template <typename T>
T FromString(const std::string &str)
  requires(std::is_floating_point_v<T>)
{
  return FromString<T>(str.data());
}

template <typename T>
T FromString(std::string_view str)
  requires(std::is_floating_point_v<T>)
{
  static constexpr std::size_t kSmallBufferSize = 32;

  if (str.size() >= kSmallBufferSize) { return FromString<T>(std::string {str}); }

  char buffer[kSmallBufferSize];
  std::copy(str.data(), str.data() + str.size(), buffer);
  buffer[str.size()] = '\0';

  return FromString<T>(buffer);
}

template <typename T>
T FromString(std::string_view str)
  requires(meta::kIsInteger<T>)
{
  static_assert(!std::is_const_v<T> && !std::is_volatile_v<T>);
  static_assert(!std::is_reference_v<T>);

  if (str.empty()) { impl::ThrowFromStringException("empty string", str, typeid(T)); }
  if (std::isspace(str[0])) { impl::ThrowFromStringException("leading spaces are not allowed", str, typeid(T)); }

  std::size_t offset = 0;

  // to allow leading plus
  if (str.size() > 1 && str[0] == '+' && str[1] == '-') {
    impl::ThrowFromStringException("no number found", str, typeid(T));
  }
  if (str[0] == '+') offset = 1;

  // to process '-0' correctly
  if (std::is_unsigned_v<T> && str[0] == '-') offset = 1;

  T result {};
  const auto [end, error_code] = std::from_chars(str.data() + offset, str.data() + str.size(), result);

  if (error_code == std::errc::result_out_of_range) { impl::ThrowFromStringException("overflow", str, typeid(T)); }
  if (error_code == std::errc::invalid_argument) { impl::ThrowFromStringException("no number found", str, typeid(T)); }

  if (std::is_unsigned_v<T> && str[0] == '-' && result != 0) {
    impl::ThrowFromStringException("overflow", str, typeid(T));
  }

  if (end != str.data() + str.size()) {
    if (std::isspace(*end)) {
      impl::ThrowFromStringException("trailing spaces are not allowed", str, typeid(T));
    } else {
      impl::ThrowFromStringException("extra junk at the end of the string is not allowed", str, typeid(T));
    }
  }

  return result;
}

}  // namespace impl

/// @brief Extract the number contained in the string. No space characters or
/// other extra characters allowed. Supported types:
///
/// - Integer types. Leading plus or minus is allowed. The number is always
///   base-10.
/// - Floating-point types. The accepted number format is identical to
///   `std::strtod`.
///
/// @tparam T The type of the number to be parsed
/// @param str The string that contains the number
/// @return The extracted number
/// @throw std::runtime_error if the string does not contain an integer or
/// floating-point number in the specified format, or the string contains extra
/// junk, or the number does not fit into the provided type
template <typename T, typename StringType>
T FromString(const StringType &str)
  requires(std::is_convertible_v<StringType, std::string_view>)
{
  return impl::FromString<T>(str);
}

std::int64_t FromHexString(const std::string &str);

}  // namespace utils
