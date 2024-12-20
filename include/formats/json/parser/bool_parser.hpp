#pragma once

#include <formats/json/parser/typed_parser.hpp>

namespace formats::json::parser {

class BoolParser final : public formats::json::parser::TypedParser<bool> {
public:
  using formats::json::parser::TypedParser<bool>::TypedParser;

protected:
  void Bool(bool b) override;

  std::string GetPathItem() const override;

  std::string Expected() const override;
};

}  // namespace formats::json::parser
