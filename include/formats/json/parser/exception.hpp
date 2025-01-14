#pragma once

#include <fmt/format.h>

#include <formats/json/exception.hpp>

namespace formats::json::parser {

class BaseError : public formats::json::Exception {
  using Exception::Exception;
};

class ParseError : public BaseError {
public:
  ParseError(size_t pos, std::string_view path, std::string what)
      : BaseError(fmt::format("Parse error at pos {}, path '{}': {}", pos, path, what)) {}
};

class InternalParseError : public BaseError {
  using BaseError::BaseError;
};

}  // namespace formats::json::parser
