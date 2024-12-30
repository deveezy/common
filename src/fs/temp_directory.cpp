#include <fs/temp_directory.hpp>

#include <utility>

#include <fmt/format.h>

#include <fs/write.hpp>
// #include <logging/log.hpp>
#include <utils/algo.hpp>
#include <utils/check_syscall.hpp>
#include "utils/assert.hpp"

namespace fs {

namespace {

void RemoveDirectory(const std::string &path) {
  std::error_code code;
  std::filesystem::remove_all(path, code);
  if (code) {
    throw std::system_error(std::make_error_code(static_cast<std::errc>(code.value())),
        fmt::format("Failed to remove directory \"{}\"", path));
  }
}

}  // namespace

TempDirectory TempDirectory::Create() { return Create(std::filesystem::temp_directory_path().string(), "userver-"); }

TempDirectory TempDirectory::Create(std::string_view parent_path, std::string_view name_prefix) {
  CreateDirectories(parent_path, std::filesystem::perms::owner_all);
  auto path = utils::StrCat(parent_path, "/", name_prefix, "XXXXXX");
  utils::CheckSyscallNotEquals(::mkdtemp(path.data()), nullptr, "::mkdtemp");
  // LOG_DEBUG() << "Created a temporary directory: " << path;
  return TempDirectory {std::move(path)};
}

TempDirectory::TempDirectory(std::string &&path) : path_(std::move(path)) {
  ASSERT(std::filesystem::is_directory(path_));
}

TempDirectory::TempDirectory(TempDirectory &&other) noexcept : path_(std::exchange(other.path_, {})) {}

TempDirectory &TempDirectory::operator=(TempDirectory &&other) noexcept {
  if (&other != this) {
    const TempDirectory temp = std::move(*this);
    path_                    = std::exchange(other.path_, {});
  }
  return *this;
}

TempDirectory::~TempDirectory() {
  if (path_.empty()) return;

  try {
    RemoveDirectory(path_);
  } catch (const std::exception &ex) {
    // LOG_ERROR() << ex;
  }
}

TempDirectory TempDirectory::Adopt(std::string path) { return TempDirectory {std::move(path)}; }

const std::string &TempDirectory::GetPath() const { return path_; }

void TempDirectory::Remove() && {
  if (path_.empty()) { throw std::runtime_error("Remove called for an already removed TempDirectory"); }
  RemoveDirectory(std::exchange(path_, {}));
}

}  // namespace fs
