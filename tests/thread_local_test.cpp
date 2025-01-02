#include <compiler/thread_local.hpp>

#include <random>
#include <string>
#include <string_view>
#include <unordered_set>

#include <gtest/gtest.h>

#include <fs/file_descriptor.hpp>
#include <fs/read.hpp>
#include <fs/temp_file.hpp>
#include <utils/rand.hpp>
#include <utils/span.hpp>

namespace {

/// [sample definition]
// NOTE: the thread-local itself should be:
// * NEVER `thread_local`
// * `static` where appropriate
// * `inline` where appropriate
compiler::ThreadLocal<std::string> local_buffer;
/// [sample definition]

/// [sample]
void WriteAll(fs::FileDescriptor &fd, std::span<const std::string_view> data) {
  // If we just write one item in `data` after the other, we might perform too
  // many syscall-s, because each of the strings may be short.
  //
  // So let's somehow concatenate `data` into a single string. But now there
  // may be too many allocations if such an operation is frequent.
  //
  // Solution: use a thread_local buffer to only allocate once per thread.

  // NOTE: the scope should be non-static, non-thread_local.
  auto buffer = local_buffer.Use();

  buffer->clear();
  for (const auto piece : data) { buffer->append(piece); }
  fd.Write(*buffer);
}
/// [sample]

TEST(ThreadLocal, Sample) {
  const auto temp_file = fs::TempFile::Create();
  {
    auto fd = fs::FileDescriptor::Open(temp_file.GetPath(), fs::OpenFlag::kWrite);
    const std::string_view data[] {"foo", "bar", "baz"};
    WriteAll(fd, data);
  }
  EXPECT_EQ(fs::ReadFileContents(temp_file.GetPath()), "foobarbaz");
}

/// [sample factory]
// NOTE: if you need thread-local randomness, don't roll your own!
// See <userver/utils/rand.hpp> and <userver/crypto/random.hpp> first!
compiler::ThreadLocal local_rng = [] { return std::minstd_rand {utils::Rand()}; };

std::uint32_t MyRand() {
  auto rng = local_rng.Use();
  return std::uniform_int_distribution<std::uint32_t> {}(*rng);
}
/// [sample factory]

TEST(ThreadLocal, SampleFactory) {
  static constexpr int kIterations = 100;
  std::unordered_set<std::uint32_t> values;
  for (int i = 0; i < kIterations; ++i) { values.insert(MyRand()); }
  // The probability of this test failing is on the order of 2^(-3200).
  EXPECT_GE(values.size(), 2);
}

}  // namespace
