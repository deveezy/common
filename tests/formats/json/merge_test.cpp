#include "../common/merge_test.hpp"

#include <gtest/gtest-typed-test.h>

#include <formats/json/serialize.hpp>
#include <formats/json/value.hpp>

template <>
class FormatsMerge<formats::json::Value> : public ::testing::Test {
public:
  constexpr static auto CheckMerge = CheckJsonMerge<formats::json::Value, formats::json::FromString>;
};

INSTANTIATE_TYPED_TEST_SUITE_P(JsonMerge, FormatsMerge, formats::json::Value);
