#pragma once

#include <formats/json/impl/types.hpp>

namespace formats::json::impl {

/// Check whether two json trees are equal
bool AreEqual(const Value *lhs, const Value *rhs);

}  // namespace formats::json::impl
