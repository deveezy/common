#include "accept.hpp"

#include <algorithm>

namespace formats::json::impl {

void InplaceSortObjectChildren(impl::Value &value) {
  std::sort(value.MemberBegin(), value.MemberEnd(), [](const auto &lhs, const auto &rhs) {
    return std::string_view(lhs.name.GetString(), lhs.name.GetStringLength()) <
           std::string_view(rhs.name.GetString(), rhs.name.GetStringLength());
  });
}

}  // namespace formats::json::impl
