#pragma once

/// @brief Parsers and serializers to/from string and stream

#include <iosfwd>

#include <formats/yaml/value.hpp>

namespace formats::yaml {

/// Parse YAML from string
formats::yaml::Value FromString(const std::string &doc);

/// Parse YAML from stream
formats::yaml::Value FromStream(std::istream &is);

/// Serialize YAML to stream
void Serialize(const formats::yaml::Value &doc, std::ostream &os);

/// Serialize YAML to string
std::string ToString(const formats::yaml::Value &doc);

/// Blocking operations that should not be used on main task processor after
/// startup
namespace blocking {
/// Read YAML from file
formats::yaml::Value FromFile(const std::string &path);
}  // namespace blocking

}  // namespace formats::yaml
