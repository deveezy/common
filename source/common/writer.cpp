#include "system/environment.hpp"
#include <common/writer.hpp>

namespace common
{

size_t Writer::Write(const std::string &_text) { return Write(_text.c_str(), _text.size()); }

size_t Writer::Write(const std::vector<std::string> &_lines) {
  static std::string endline = Environment::EndLine();
  size_t result = 0;
  for (const auto &line : _lines) {
    if (Write(line.c_str(), line.size()) != line.size()) break;
    if (Write(endline.c_str(), endline.size()) != endline.size()) break;
    ++result;
  }
  return result;
}

} // namespace common
