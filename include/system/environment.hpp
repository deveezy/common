#pragma once

#include <map>
#include <string>

namespace common
{
// Thread-safe.
class Environment
{
public:
  Environment() = delete;
  Environment(const Environment &) = delete;
  Environment(Environment &&) = delete;
  Environment &operator=(const Environment &) = delete;
  Environment &operator=(Environment &&) = delete;

  static bool Is32BitOS();
  static bool Is64BitOS();

  static bool Is32BitProcess();
  static bool Is64BitProcess();

  // Is compiled in debug mode?
  static bool IsDebug();
  static bool IsRelease();

  static bool IsBigEndian();
  static bool IsLitterEndian();

  static std::string OSVersion();

  // Get text end line seprator ("\r\n or \n")
  static std::string EndLine();

  static std::string UnixEndline();
  static std::string WindowsEndLine();

  // Get all env variables
  static std::map<std::string, std::string> envars();

  // Get env var value by the given name
  static std::string GetEnvar(const std::string _name);

  static void SetEnvar(const std::string _name, const std::string _value);

  static void ClearEnvar(const std::string _name);
};
} // namespace common
