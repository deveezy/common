#include "../common/merge_test.hpp"

#include <gtest/gtest-typed-test.h>

#include <formats/yaml/serialize.hpp>
#include <formats/yaml/value.hpp>

template <>
class FormatsMerge<formats::yaml::Value> : public ::testing::Test {
public:
  constexpr static auto CheckMerge = CheckJsonMerge<formats::yaml::Value, formats::yaml::FromString>;
};

INSTANTIATE_TYPED_TEST_SUITE_P(YamlMerge, FormatsMerge, formats::yaml::Value);
