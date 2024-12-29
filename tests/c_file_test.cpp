#include <fs/c_file.hpp>

#include <gtest/gtest.h>

#include <fs/read.hpp>
#include <fs/temp_directory.hpp>
#include <fs/temp_file.hpp>
#include <fs/write.hpp>

TEST(CFile, NullFile) {
  fs::CFile file;
  EXPECT_FALSE(file.IsOpen());
}

TEST(CFile, DirectPointer) {
  const auto file_scope = fs::TempFile::Create();
  fs::CFile file(std::fopen("file", "w"));
  EXPECT_TRUE(file.IsOpen());
  EXPECT_NO_THROW(file.Write("Test write data\n"));
}

TEST(CFile, Move) {
  const auto file1 = fs::TempFile::Create();
  fs::RewriteFileContents(file1.GetPath(), "bar");

  fs::CFile reader1(file1.GetPath(), fs::OpenFlag::kRead);
  EXPECT_TRUE(reader1.IsOpen());

  fs::CFile reader2 = std::move(reader1);
  EXPECT_TRUE(reader2.IsOpen());

  fs::CFile reader3;
  EXPECT_FALSE(reader3.IsOpen());
  reader3 = std::move(reader2);
  EXPECT_TRUE(reader3.IsOpen());

  const auto file2 = fs::TempFile::Create();
  fs::RewriteFileContents(file2.GetPath(), "qux");
  fs::CFile reader4(file2.GetPath(), fs::OpenFlag::kRead);
  EXPECT_TRUE(reader4.IsOpen());
  reader4 = std::move(reader3);
  EXPECT_TRUE(reader4.IsOpen());
}

TEST(CFile, Reading) {
  const auto file = fs::TempFile::Create();
  fs::RewriteFileContents(file.GetPath(), "bar");

  fs::CFile reader(file.GetPath(), fs::OpenFlag::kRead);
  EXPECT_TRUE(reader.IsOpen());

  std::string buffer(10, '\0');
  EXPECT_EQ(reader.Read(buffer.data(), 1), 1);
  EXPECT_EQ(reader.Read(buffer.data(), 10), 2);

  std::move(reader).Close();
  // NOLINTNEXTLINE(bugprone-use-after-move)
  EXPECT_FALSE(reader.IsOpen());
}

TEST(CFile, Writing) {
  const auto dir         = fs::TempDirectory::Create();
  const std::string path = dir.GetPath() + "/foo";

  // file does not exist yet
  EXPECT_THROW(fs::CFile(path, fs::OpenFlag::kWrite), std::runtime_error);

  fs::CFile file(path, {fs::OpenFlag::kWrite, fs::OpenFlag::kCreateIfNotExists});
  file.Write("bar");
  file.Write("baz");
  file.Flush();

  EXPECT_EQ(fs::ReadFileContents(path), "barbaz");
}

TEST(CFile, WriteEmpty) {
  const auto dir         = fs::TempDirectory::Create();
  const std::string path = dir.GetPath() + "/foo";

  fs::CFile file(path, {fs::OpenFlag::kWrite, fs::OpenFlag::kCreateIfNotExists});
  file.Write(std::string_view {});
  file.Flush();

  EXPECT_EQ(fs::ReadFileContents(path), "");
}

TEST(CFile, Position) {
  const auto dir         = fs::TempDirectory::Create();
  const std::string path = dir.GetPath() + "/foo";

  {
    fs::CFile writer(path, {fs::OpenFlag::kWrite, fs::OpenFlag::kCreateIfNotExists});
    EXPECT_EQ(writer.GetPosition(), 0);
    EXPECT_EQ(writer.GetSize(), 0);

    writer.Write("CFile");
    EXPECT_EQ(writer.GetPosition(), 5);

    writer.Flush();
    EXPECT_EQ(writer.GetSize(), 5);
  }

  {
    std::string buffer(5, '\0');

    fs::CFile reader(path, fs::OpenFlag::kRead);
    EXPECT_EQ(reader.GetPosition(), 0);
    EXPECT_EQ(reader.GetSize(), 5);

    EXPECT_EQ(reader.Read(buffer.data(), 3), 3);
    EXPECT_EQ(reader.GetPosition(), 3);
    EXPECT_EQ(reader.GetSize(), 5);

    EXPECT_EQ(reader.Read(buffer.data(), 10), 2);
    EXPECT_EQ(reader.GetPosition(), 5);
    EXPECT_EQ(reader.GetSize(), 5);
  }
}
