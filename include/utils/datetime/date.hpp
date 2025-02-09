#pragma once

/// @brief @copybrief utils::datetime::Date

#include <chrono>
#include <iosfwd>
#include <stdexcept>
#include <string>

#include <formats/common/meta.hpp>

/// Date and time utilities
namespace utils::datetime {

///
/// @brief Date in format YYYY-MM-DD, std::chrono::year_month_day like type.
///
/// Convertible to std::sys_days and could be constructed from year,
/// month and day integers.
class Date final {
public:
  using Days    = std::chrono::duration<long long, std::ratio<86400>>;
  using SysDays = std::chrono::time_point<std::chrono::system_clock, Days>;

  Date()                                 = default;
  Date(const Date &) noexcept            = default;
  Date &operator=(const Date &) noexcept = default;

  /// @brief Constructs Date without validation of input arguments
  Date(int year, int month, int day);

  /// @brief constructor from system clock time point in days.
  constexpr Date(SysDays tp) noexcept : sys_days_(tp) {}

  /// @brief Returns a time point corresponding to the date.
  ///
  /// This function may return the same time point, that was passed to
  /// constructor.
  constexpr SysDays GetSysDays() const { return sys_days_; }

  /// @copydoc GetSysDays()
  constexpr explicit operator SysDays() const { return sys_days_; }

  constexpr bool operator==(Date other) const { return sys_days_ == other.sys_days_; }
  constexpr bool operator!=(Date other) const { return !(*this == other); }

private:
  SysDays sys_days_;
};

/// Validates date_string and constructs date from YYYY-MM-DD string and
Date DateFromRFC3339String(const std::string &date_string);

/// Outputs date as a YYYY-MM-DD string
std::string ToString(Date date);

template <typename Value>
Date Parse(const Value &value, formats::parse::To<Date>)
  requires(formats::common::kIsFormatValue<Value>)
{
  std::string str;
  try {
    str = value.template As<std::string>();
  } catch (const std::exception &e) {
    throw typename Value::ParseException("Only strings can be parsed as `utils::datetime::Date`");
  }

  try {
    return utils::datetime::DateFromRFC3339String(str);
  } catch (const std::exception &e) {
    throw typename Value::ParseException("'" + str + "' cannot be parsed to `utils::datetime::Date`");
  }
}

template <typename Value>
Value Serialize(Date date, formats::serialize::To<Value>)
  requires(formats::common::kIsFormatValue<Value>)
{
  return typename Value::Builder(ToString(date)).ExtractValue();
}

template <typename StringBuilder>
void WriteToStream(Date value, StringBuilder &sw) {
  WriteToStream(ToString(value), sw);
}

std::ostream &operator<<(std::ostream &os, Date date);

}  // namespace utils::datetime
