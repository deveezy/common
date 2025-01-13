#pragma once

/// @brief Assertion macros ASSERT, ASSERT_MSG, INVARIANT

#include <string_view>

namespace utils::impl {

[[noreturn]] void ASSERT_failed(
    std::string_view expr, const char *file, unsigned int line, const char *function, std::string_view msg) noexcept;

[[noreturn]] void LogAndThrowInvariantError(std::string_view condition, std::string_view message);

#ifdef NDEBUG
inline constexpr bool kEnableAssert = false;
#else
inline constexpr bool kEnableAssert = true;
#endif

extern bool dump_stacktrace_on_assert_failure;

[[noreturn]] void AbortWithStacktrace(std::string_view message) noexcept;

}  // namespace utils::impl

/// @brief Assertion macro for that aborts execution in DEBUG builds with a
/// message `msg` and does nothing in release builds
///
/// @hideinitializer
// NOLINTNEXTLINE (cppcoreguidelines-macro-usage)
#define ASSERT_MSG(expr, msg)                                                 \
  do {                                                                        \
    if (utils::impl::kEnableAssert) {                                         \
      if (expr) {                                                             \
      } else {                                                                \
        utils::impl::ASSERT_failed(#expr, __FILE__, __LINE__, __func__, msg); \
      }                                                                       \
    }                                                                         \
  } while (0)

/// @brief Assertion macro that aborts execution in DEBUG builds and does
/// nothing in release builds
///
/// @hideinitializer
// NOLINTNEXTLINE (cppcoreguidelines-macro-usage)
#define ASSERT(expr) ASSERT_MSG(expr, std::string_view {})

/// @brief Asserts in debug builds, throws utils::InvariantError in release
///
/// @hideinitializer
// NOLINTNEXTLINE (cppcoreguidelines-macro-usage)
#define INVARIANT(condition, message)                                                  \
  do {                                                                                 \
    if (condition) {                                                                   \
    } else {                                                                           \
      if constexpr (utils::impl::kEnableAssert) {                                      \
        utils::impl::ASSERT_failed(#condition, __FILE__, __LINE__, __func__, message); \
      } else {                                                                         \
        utils::impl::LogAndThrowInvariantError(#condition, message);                   \
      }                                                                                \
    }                                                                                  \
  } while (0)
