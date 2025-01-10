#include <utils/assert.hpp>

#include <iostream>

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <boost/stacktrace/stacktrace.hpp>

// #include <logging/log.hpp>
#include <utils/invariant_error.hpp>

namespace utils::impl {

[[noreturn]] void AbortWithStacktrace(std::string_view message) noexcept {
  if (dump_stacktrace_on_assert_failure) {
    // TODO(44444): log
    // LOG_CRITICAL() << message << logging::LogExtra::Stacktrace();
  } else {
    // TODO(44444): log
    // LOG_CRITICAL() << message;
  }
  // TODO(44444): log
  // logging::LogFlush();

  auto trace =
      dump_stacktrace_on_assert_failure ? boost::stacktrace::stacktrace() : boost::stacktrace::stacktrace(0, 0);

  // Use fmt::format to output the message without interleaving with other logs.
  std::cerr << fmt::format("{}. Stacktrace:\n{}", message, boost::stacktrace::to_string(trace));
  std::abort();
}

void ASSERT_failed(
    std::string_view expr, const char *file, unsigned int line, const char *function, std::string_view msg) noexcept {
  // TODO pass file, line, function to LogHelper
  const auto message = fmt::format("ERROR at {}:{}:{}. Assertion '{}' failed{}{}", file, line,
      (function ? function : ""), expr, (msg.empty() ? std::string_view {} : std::string_view {": "}), msg);
  AbortWithStacktrace(message);
}

void LogAndThrowInvariantError(std::string_view condition, std::string_view message) {
  const auto err_str = ::fmt::format("Invariant ({}) violation: {}", condition, message);

  // TODO(44444): log instead of cerr
  // LOG_ERROR() << err_str;
  std::cerr << err_str << std::endl;
  throw InvariantError(err_str);
}

bool dump_stacktrace_on_assert_failure = true;

}  // namespace utils::impl

// Function definitions for defined BOOST_ENABLE_ASSERT_HANDLER
namespace boost {
void assertion_failed(char const *expr, char const *function, char const *file, long line) {
  utils::impl::ASSERT_failed(expr, file, line, function, {});
}

void assertion_failed_msg(char const *expr, char const *msg, char const *function, char const *file, long line) {
  utils::impl::ASSERT_failed(expr, file, line, function, msg);
}
}  // namespace boost
