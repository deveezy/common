#pragma once

/// @brief utils::datetime::TimeOfDay parser for any format
///

#include <utils/time_of_day.hpp>

#include <formats/common/meta.hpp>
#include <formats/parse/to.hpp>

namespace formats::parse {

template <typename Value, typename Duration>
utils::datetime::TimeOfDay<Duration> Parse(const Value &value, To<utils::datetime::TimeOfDay<Duration>>)
  requires(common::kIsFormatValue<Value>)
{
  std::optional<std::string> str;
  try {
    str = value.template As<std::string>();
    return utils::datetime::TimeOfDay<Duration> {*str};
  } catch (const std::exception &e) {
    if (str) {
      throw typename Value::ParseException("'" + *str + "' cannot be parsed to `utils::datetime::TimeOfDay`");
    } else {
      throw typename Value::ParseException("Only strings can be parsed as `utils::datetime::TimeOfDay`");
    }
  }
}

}  // namespace formats::parse
