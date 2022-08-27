#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace common
{
class Writer
{
public:
  Writer() noexcept = default;
  Writer(const Writer &) noexcept = default;
  Writer(Writer &&) noexcept = default;
  virtual ~Writer() noexcept = default;

  Writer &operator=(const Writer &) noexcept = default;
  Writer &operator=(Writer &&) noexcept = default;

  // return count of written bytes
  virtual size_t Write(const void *_buffer, size_t _size) = 0;

  // return count of written characters
  size_t Write(const std::string &_text);

  // return count of written lines
  size_t Write(const std::vector<std::string> &_lines);

  virtual void Flush() {}
};
} // namespace common
