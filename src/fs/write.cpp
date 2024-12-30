#include <fs/write.hpp>

#include <sys/stat.h>
#include <cerrno>
#include <system_error>

#include <fmt/format.h>
#include <boost/filesystem/operations.hpp>

#include <fs/file_descriptor.hpp>
#include <utils/assert.hpp>
#include <utils/uuid4.hpp>
// #include <utils/boost_uuid4.hpp>
#include <utils/fast_scope_guard.hpp>

namespace fs {

namespace {

void CreateDirectory(const char *path, boost::filesystem::perms perms) {
  if (::mkdir(path, static_cast<::mode_t>(perms)) == -1) {
    const auto code = errno;
    if (code != EEXIST) {
      throw std::system_error(
          code, std::generic_category(), fmt::format("Error while creating directory \"{}\"", path));
    }
  }
}

}  // namespace

void CreateDirectories(std::string_view path, boost::filesystem::perms perms) {
  ASSERT(!path.empty());

  std::string mutable_path;
  mutable_path.reserve(path.size() + 2);
  mutable_path.append(path);
  mutable_path.push_back('/');
  mutable_path.push_back('\0');

  for (char *p = mutable_path.data() + 1; *p != '\0'; ++p) {
    if (*p == '/') {
      *p = '\0';  // temporarily truncate
      CreateDirectory(mutable_path.data(), perms);
      *p = '/';
    }
  }
}

void CreateDirectories(std::string_view path) {
  using boost::filesystem::perms;
  const auto kPerms0755 =
      perms::owner_all | perms::group_read | perms::group_exe | perms::others_read | perms::others_exe;
  CreateDirectories(path, kPerms0755);
}

void RewriteFileContents(const std::string &path, std::string_view contents) {
  constexpr OpenMode flags {OpenFlag::kWrite, OpenFlag::kCreateIfNotExists, OpenFlag::kTruncate};
  auto fd = FileDescriptor::Open(path, flags);

  fd.Write(contents);
  std::move(fd).Close();
}

void RewriteFileContentsFSync(const std::string &path, std::string_view contents) {
  constexpr OpenMode flags {OpenFlag::kWrite, OpenFlag::kCreateIfNotExists, OpenFlag::kTruncate};
  auto fd = FileDescriptor::Open(path, flags);
  fd.Write(contents);
  fd.FSync();

  std::move(fd).Close();
}

void SyncDirectoryContents(const std::string &path) {
  auto fd = FileDescriptor::OpenDirectory(path);
  fd.FSync();
  std::move(fd).Close();
}

void Rename(const std::string &source, const std::string &destination) {
  boost::filesystem::rename(source, destination);
}

void RewriteFileContentsAtomically(const std::string &path, std::string_view contents, std::filesystem::perms perms) {
  const auto tmp_path = fmt::format("{}{}.tmp", path, utils::generators::GenerateUuidV4());
  const std::filesystem::path tmpPath {tmp_path};
  const auto directory = tmpPath.parent_path().string();

  utils::FastScopeGuard guard {[&tmpPath]() noexcept { std::filesystem::remove(tmpPath); }};
  fs::RewriteFileContentsFSync(tmp_path, contents);
  fs::Chmod(tmp_path, perms);
  fs::Rename(tmp_path, path);
  guard.Release();

  fs::SyncDirectoryContents(directory);
}

void Chmod(const std::string &path, boost::filesystem::perms perms) { boost::filesystem::permissions(path, perms); }

bool RemoveSingleFile(const std::string &path) { return boost::filesystem::remove(path); }

}  // namespace fs
