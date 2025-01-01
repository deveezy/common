// #include <utils/time_of_day.hpp>
#include <iostream>

#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>

struct QuotableString : std::string_view {};

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
  // QuotableString a("be"), a2(R"( " be " )");
  // QuotableString b("a question");
  // std::cout << std::format("To {0} or not to {0}, that is {1}.\n", a, b);
  // std::cout << std::format("To {0:} or not to {0:}, that is {1:}.\n", a, b);
  // std::cout << std::format("To {0:#} or not to {0:#}, that is {1:#}.\n", a2, b);

  const char *names[] = {"Alex", "John"};
  std::string str     = names[2];
  return str.length();
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
