#include <formats/json/parser/bool_parser.hpp>

namespace formats::json::parser {

void BoolParser::Bool(bool b) { SetResult(std::move(b)); }

std::string BoolParser::GetPathItem() const { return {}; }

std::string BoolParser::Expected() const { return "bool"; }

}  // namespace formats::json::parser
