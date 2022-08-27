#pragma once
#include <cstddef>

namespace common
{
template <typename T, size_t N>
constexpr size_t countof(const T (&)[N]) noexcept {
  return N;
}

template <typename T>
size_t countof(const T &_container) noexcept {
  return _container.size();
}
} // namespace common
