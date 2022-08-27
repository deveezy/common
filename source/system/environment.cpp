#include <cstring>
#include <fstream>
#include <regex>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <system/environment.hpp>

#if defined(unix) || defined(__unix) || defined(__unix__)
extern char **environ;
// TODO: impl on other platforms
#endif

namespace common
{

bool Environment::Is32BitOS() { return !Is64BitOS(); }

bool Environment::Is64BitOS() {
  struct stat buffer;
  return (stat("/lib64/ld-linux-x86-64.so.2", &buffer) == 0);
}

bool Environment::Is32BitProcess() { return !Is64BitProcess(); }

bool Environment::Is64BitProcess() {
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
#if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__ia64__) ||      \
  defined(__ppc64__)
  return true;
#else
  return false;
#endif
#elif defined(_WIN32) || defined(_WIN64) j
#if defined(_WIN64)
  return true;
#elif defined(_WIN32)
  return false;
#endif
#else
#error Unsupported platform
#endif
}

bool Environment::IsDebug() { return !IsRelease(); }

bool Environment::IsRelease() {
#if defined(NDEBUG)
  return true;
#else
  return false;
#endif
}

bool Environment::IsBigEndian() {
  char16_t test = 0x0102;
  return ((char *)&test)[0] == 0x01;
}

bool Environment::IsLitterEndian() {
  char16_t test = 0x0102;
  return ((char *)&test)[0] == 0x02;
}

std::string Environment::OSVersion() {
  std::string os_version;
#if defined(linux) || defined(__linux) || defined(__linux__)
  utsname buf;
  if (uname(&buf) != -1) {
    os_version += std::string{buf.sysname} + " " + std::string{buf.machine} +
                  " VER: " + std::string{buf.version};
  }
#else
  // TODO: impl for mac/win
#error Unsupported platform
#endif
  return os_version;
}

std::string Environment::EndLine() {
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
  return "\n";
#elif defined(_WIN32) || defined(_WIN64)
  return "\r\n";
#else
#error Unsupported platform
#endif
}

std::string Environment::UnixEndline() { return "\n"; }

std::string Environment::WindowsEndLine() { return "\r\n"; }

std::map<std::string, std::string> Environment::envars() {
  std::map<std::string, std::string> res;
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
  for (char **envars = environ; *envars; ++envars) {
    const char *envar = *envars;
    const int offset = (envar[0] == '=') ? 1 : 0;
    const char *sep = std::strchr(envar + offset, '=');
    if (sep != nullptr) {

      const std::string key(envar, sep - envar);

      const char *pvalue = sep + 1;
      const std::string value{pvalue};
      res[key] = value;
    }
  }
#elif #elif defined(_WIN32) || defined(_WIN64)
#endif
  return res;
}

std::string Environment::GetEnvar(const std::string _name) {
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
  char *envar = getenv(_name.c_str());
  return (envar != nullptr) ? std::string{envar} : std::string{};
#elif defined(_WIN32) || defined(_WIN64)
#endif
}

void Environment::SetEnvar(const std::string _name, const std::string _value) {
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
  if (setenv(_name.c_str(), _value.c_str(), 1) != 0)
    throwex SystemException("Cannot set environment variable - " + _name);
#elif defined(_WIN32) || defined(_WIN64)

#endif
}

void Environment::ClearEnvar(const std::string _name) {
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
  if (unsetenv(_name.c_str()) != 0)
    throwex SystemException("Cannot clear environment variable - " + _name);
#elif defined(_WIN32) || defined(_WIN64)
  if (!SetEnvironmentVariableW(Encoding::FromUTF8(name).c_str(), nullptr))
    throwex SystemException("Cannot clear environment variable - " + name);
#endif
}

} // namespace common
