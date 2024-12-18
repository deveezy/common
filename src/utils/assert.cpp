#include <utils/assert.hpp>

#include <iostream>
// #include <fmt/format.h>

namespace utils::impl {

[[noreturn]] void AbortWithStacktrace(std::string_view message) noexcept {
  if (dump_stacktrace_on_assert_failure) {
    std::cerr << message << std::endl;
  } else {
    std::cerr << message << std::endl;
  }

  // delete uCLog::instance();
  std::abort();
}

void UASSERT_failed(
    std::string_view expr, const char *file, unsigned int line, const char *function, std::string_view msg) noexcept {
  // TODO pass file, line, function to LogHelper
  const auto message = std::format("ERROR at {}:{}:{}. Assertion '{}' failed{}{}", file, line,
      (function ? function : ""), expr, (msg.empty() ? std::string_view {} : std::string_view {": "}), msg);

  AbortWithStacktrace(message);
}

void LogAndThrowInvariantError(std::string_view condition, std::string_view message) {
  // const auto err_str = ::fmt::format("Invariant ({}) violation: {}", condition, message);

  const auto err_str = ::std::format("Invariant ({}) violation: {}", condition, message);

  std::cerr << err_str << std::endl;
  throw std::runtime_error(err_str);
}

bool dump_stacktrace_on_assert_failure = true;

}  // namespace utils::impl

// Function definitions for defined BOOST_ENABLE_ASSERT_HANDLER
