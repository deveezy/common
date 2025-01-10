#include <utils/traceful_exception.hpp>

#include <fmt/compile.h>
#include <fmt/format.h>
#include <boost/stacktrace/stacktrace.hpp>

// #include <logging/log_extra_stacktrace.hpp>

namespace utils {

namespace {

// TODO(44444): depends on log level
#if NDEBUG
constexpr auto shouldLogStacktrace = false;
#else
constexpr auto shouldLogStacktrace = true;
#endif
boost::stacktrace::stacktrace CollectTrace(TracefulException::TraceMode trace_mode) {
  if (trace_mode == TracefulException::TraceMode::kIfLoggingIsEnabled && !shouldLogStacktrace) { return {0, 0}; }
  return {};
}

}  // namespace

struct TracefulExceptionBase::Impl final {
  explicit Impl(TraceMode trace_mode) : stacktrace_(CollectTrace(trace_mode)) {}

  MemoryBuffer message_buffer_;
  boost::stacktrace::stacktrace stacktrace_;
};

TracefulExceptionBase::TracefulExceptionBase(TracefulExceptionBase &&other) noexcept : impl_(std::move(other.impl_)) {
  EnsureNullTerminated();
}

TracefulExceptionBase::~TracefulExceptionBase() = default;

void TracefulExceptionBase::EnsureNullTerminated() {
  impl_->message_buffer_.reserve(impl_->message_buffer_.size() + 1);
  impl_->message_buffer_[impl_->message_buffer_.size()] = '\0';
}

const char *TracefulException::what() const noexcept {
  return MessageBuffer().size() != 0 ? MessageBuffer().data() : std::exception::what();
}

const TracefulExceptionBase::MemoryBuffer &TracefulExceptionBase::MessageBuffer() const noexcept {
  return impl_->message_buffer_;
}

const boost::stacktrace::stacktrace &TracefulExceptionBase::Trace() const noexcept { return impl_->stacktrace_; }

TracefulExceptionBase::TracefulExceptionBase() : TracefulExceptionBase(TraceMode::kAlways) {}

TracefulExceptionBase::TracefulExceptionBase(std::string_view what) : TracefulExceptionBase(TraceMode::kAlways) {
  fmt::format_to(std::back_inserter(impl_->message_buffer_), FMT_COMPILE("{}"), what);
  EnsureNullTerminated();
}

TracefulExceptionBase::TracefulExceptionBase(TraceMode trace_mode) : impl_(trace_mode) {}

TracefulExceptionBase::MemoryBuffer &TracefulExceptionBase::GetMessageBuffer() { return impl_->message_buffer_; }

}  // namespace utils
