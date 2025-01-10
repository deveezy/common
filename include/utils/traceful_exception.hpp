#pragma once

/// @file userver/utils/traceful_exception.hpp
/// @brief @copybrief utils::TracefulException

#include <exception>
#include <type_traits>

#include <fmt/format.h>
#include <boost/stacktrace/stacktrace_fwd.hpp>

#include <compiler/select.hpp>
#include <utils/fast_pimpl.hpp>

namespace utils {

/// @brief Base class implementing backtrace storage and message builder,
/// published only for documentation purposes, please inherit from
/// utils::TracefulException instead.
class TracefulExceptionBase {
public:
  enum class TraceMode {
    kAlways,
    kIfLoggingIsEnabled,
  };

  static constexpr size_t kInlineBufferSize = 100;
  using MemoryBuffer                        = fmt::basic_memory_buffer<char, kInlineBufferSize>;

  TracefulExceptionBase();

  explicit TracefulExceptionBase(std::string_view what);

  explicit TracefulExceptionBase(TraceMode trace_mode);

  TracefulExceptionBase(TracefulExceptionBase &&) noexcept;
  virtual ~TracefulExceptionBase() = 0;

  const MemoryBuffer &MessageBuffer() const noexcept;
  const boost::stacktrace::basic_stacktrace<> &Trace() const noexcept;

  /// Stream-like interface for message extension
  template <typename Exception, typename T>
  friend Exception &&operator<<(Exception &&ex, const T &data)
    requires std::is_base_of_v<TracefulExceptionBase, typename std::remove_reference<Exception>::type>
  {
    fmt::format_to(std::back_inserter(ex.GetMessageBuffer()), "{}", data);
    ex.EnsureNullTerminated();
    return std::forward<Exception>(ex);
  }

private:
  void EnsureNullTerminated();

  MemoryBuffer &GetMessageBuffer();

  struct Impl;
  static constexpr std::size_t kSize = sizeof(MemoryBuffer) + compiler::SelectSize().For64Bit(24).For32Bit(12);
  utils::FastPimpl<Impl, kSize, alignof(void *)> impl_;
};

/// @ingroup userver_universal userver_base_classes
///
/// @brief Exception that remembers the backtrace at the point of its
/// construction
// NOLINTNEXTLINE(fuchsia-multiple-inheritance)
class TracefulException : public std::exception, public TracefulExceptionBase {
public:
  using TracefulExceptionBase::TracefulExceptionBase;

  const char *what() const noexcept override;
};

namespace impl {

template <typename PlainException>
// NOLINTNEXTLINE(fuchsia-multiple-inheritance)
class ExceptionWithAttachedTrace final : public PlainException, public TracefulExceptionBase {
public:
  explicit ExceptionWithAttachedTrace(const PlainException &ex)
      : PlainException(ex)
      , TracefulExceptionBase(ex.what()) {}
};

template <typename Exception>
ExceptionWithAttachedTrace<Exception> AttachTraceToException(const Exception &ex)
  requires std::is_base_of_v<std::exception, Exception>
{
  static_assert(!std::is_base_of_v<TracefulExceptionBase, Exception>, "This exception already contains trace");
  return ExceptionWithAttachedTrace<Exception>(ex);
}

}  // namespace impl
}  // namespace utils
