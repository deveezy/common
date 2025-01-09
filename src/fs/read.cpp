#include <fs/read.hpp>

#include <fstream>
#include <sstream>

namespace fs {

std::string ReadFileContents(const std::string &path) {
  std::ifstream ifs(path);
  if (!ifs) { throw std::runtime_error("Error opening '" + path + '\''); }

  std::ostringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}

bool FileExists(const std::string &path) { return std::filesystem::exists(path); }

std::filesystem::file_type GetFileType(const std::string &path) { return std::filesystem::status(path).type(); }

}  // namespace fs
