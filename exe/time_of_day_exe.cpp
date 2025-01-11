// #include <utils/time_of_day.hpp>
#include <iostream>

#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>

#include <formats/json/value.hpp>
#include <formats/parse/common_containers.hpp>
#include <formats/serialize/common_containers.hpp>
#include "formats/json/serialize.hpp"
#include "formats/json/value_builder.hpp"
struct QuotableString : std::string_view {};

struct CustomValue {
  std::string field1;
  int field2;
  std::vector<int> arr;
};

//  The function must be declared in the namespace of your type
CustomValue Parse(const formats::json::Value &json, formats::parse::To<CustomValue>) {
  return CustomValue {
      .field1 = json["field1"].As<std::string>(""),
      .field2 = json["field2"].As<int>(1),             // return `1` if "field2" is missing
      .arr    = json["arr"].As<std::vector<int>>({}),  // return `1` if "field2" is missing
  };
}

// The function must be declared in the namespace of your type
formats::json::Value Serialize(const CustomValue &data, formats::serialize::To<formats::json::Value>) {
  formats::json::Value::Builder builder;
  builder["field1"] = data.field1;
  builder["field2"] = data.field2;
  builder["arr"]    = data.arr;

  return builder.ExtractValue();
}

// template <>
// struct std::formatter<QuotableString, char> {
//   bool quoted = false;
//
//   template <class ParseContext>
//   constexpr ParseContext::iterator parse(ParseContext &ctx) {
//     auto it = ctx.begin();
//     if (it == ctx.end()) { return it; }
//
//     if (*it == '#') {
//       quoted = true;
//       ++it;
//     }
//     if (it != ctx.end() && *it != '}') throw std::format_error("Invalid format args for QuotableString.");
//
//     return it;
//   }
//
//   template <class FmtContext>
//   FmtContext::iterator format(QuotableString s, FmtContext &ctx) const {
//     std::ostringstream out;
//     if (quoted) {
//       out << std::quoted(s);
//     } else {
//       out << s;
//     }
//
//     return std::ranges::copy(std::move(out).str(), ctx.out()).out;
//   }
// };

int main() {
  formats::json::Value json = formats::json::FromString(R"(
{
  "store": {
    "array": [1, 2, 3, 4],
    "book": [
      {
        "category": "fiction",
        "title": "The Great Gatsby",
        "price": 10.99
      },
      {
        "category": "non-fiction",
        "title": "Sapiens",
        "price": 12.99
      }
    ],
    "bicycle": {
      "color": "red",
      "price": 19.95
    }
  }
})");

  // const auto key1 = json["key1"].As<int>();
  // json["key1"]    = 10;

  // const auto &key3 = json["key2"]["key3"].As<std::string>();
  std::cout << json["store"]["array"].IsArray() << std::endl;
  const auto arr = json["store"]["array"];
  const auto vec = arr.As<std::vector<int>>();
  std::cout << vec.size() << std::endl;
  CustomValue cust {.field1 = "string", .field2 = 10, .arr = {1, 2, 3, 4}};

  formats::json::ValueBuilder builderJson;
  builderJson["example"] = cust;
  auto json2             = builderJson.ExtractValue();
  const auto ret         = json2.As<CustomValue>();
  formats::json::ToStableString();
  // std::cout << formats::json::ToString(json2) << std::endl;
  std::cout << std::format("{}", json);

  return 0;
}

// int main() {
//   utils::datetime::TimeOfDay<std::chrono::seconds> tod {"10:20:30"};
//   std::cout << tod.Hours() << std::endl;
//   std::cout << tod.Minutes() << std::endl;
//   std::cout << tod.Seconds() << std::endl;
//   std::cout << tod.Subseconds().count();
//
//   return 0;
// }
