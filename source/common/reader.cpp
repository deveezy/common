#include <common/reader.hpp>
#include <utility/countof.hpp>

namespace common
{

std::vector<uint8_t> Reader::ReadAllBytes() {
  constexpr size_t CHUNK = 8192;

  uint8_t buffer[CHUNK];
  std::vector<uint8_t> result;
  size_t size = 0;

  do {
    size = Read(buffer, countof(buffer));
    result.insert(result.end(), buffer, buffer + size);
  } while (size == countof(buffer));
  return result;
}

std::string Reader::ReadAllText() {
  std::vector<uint8_t> bytes = ReadAllBytes();
  return std::string(bytes.begin(), bytes.end());
}

std::vector<std::string> Reader::ReadAllLines() {
  std::string tmp;
  std::vector<std::string> result;
  std::vector<uint8_t> bytes = ReadAllBytes();

  for (const auto ch : bytes) {
    if ((ch == '\r') || (ch == '\n')) {
      if (!tmp.empty()) {
        result.emplace_back(tmp);
        tmp.clear();
      }
    } else {
      tmp += ch;
    }
  }
  return result;
}

} // namespace common
