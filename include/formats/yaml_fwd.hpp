#pragma once

/// @brief Forward declarations of formats::yaml types, formats::parse::To and
/// formats::serialize::To.

#include <formats/parse/to.hpp>
#include <formats/serialize/to.hpp>

namespace formats::yaml {

// NOLINTNEXTLINE(bugprone-forward-declaration-namespace)
class Value;

// NOLINTNEXTLINE(bugprone-forward-declaration-namespace)
class ValueBuilder;

}  // namespace formats::yaml
