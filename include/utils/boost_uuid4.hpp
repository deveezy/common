#pragma once

/// @file userver/utils/boost_uuid4.hpp
/// @brief @copybrief utils::generators::GenerateBoostUuid()

#include <boost/uuid/uuid.hpp>

#include <fmt/core.h>

namespace utils {

/// Generators
namespace generators {

/// Generates UUIDv4
boost::uuids::uuid GenerateBoostUuid();

}  // namespace generators

/// Parse string into boost::uuids::uuid
boost::uuids::uuid BoostUuidFromString(std::string_view str);

/// Serialize boost::uuids::uuid to string
std::string ToString(const boost::uuids::uuid &);

}  // namespace utils

template <>
struct fmt::formatter<boost::uuids::uuid> {
  constexpr static auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const boost::uuids::uuid &uuid, FormatContext &ctx) const {
    return fmt::format_to(ctx.out(), "{}", utils::ToString(uuid));
  }
};
