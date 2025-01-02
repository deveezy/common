#include <compiler/thread_local.hpp>

#include <cstddef>

#include <utils/assert.hpp>

namespace compiler::impl {

namespace {

std::size_t &CoroutineSwitchBansCount() noexcept {
  return ThreadLocal([] { return std::size_t {0}; });
}

}  // namespace

bool AreCoroutineSwitchesAllowed() noexcept { return CoroutineSwitchBansCount() == 0; }

void IncrementLocalCoroutineSwitchBans() noexcept { ++CoroutineSwitchBansCount(); }

void DecrementLocalCoroutineSwitchBans() noexcept {
  auto &block_count = CoroutineSwitchBansCount();
  ASSERT(block_count != 0);
  --block_count;
}

}  // namespace compiler::impl
