#pragma once
#include <string>
#include <vector>

namespace common
{
class Reader
{
public:
  Reader() noexcept = default;
  Reader(const Reader &) noexcept = default;
  Reader(Reader &&) noexcept = default;
  virtual ~Reader() noexcept = default;

  Reader &operator=(const Reader &) noexcept = default;
  Reader &operator=(Reader &&) noexcept = default;

  virtual size_t Read(void *_buffer, size_t _size) = 0;

  std::vector<uint8_t> ReadAllBytes();
  std::string ReadAllText();
  std::vector<std::string> ReadAllLines();
};
} // namespace common
