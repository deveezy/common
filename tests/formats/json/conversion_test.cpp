#include <gtest/gtest.h>

#include <formats/json/value.hpp>
#include <formats/json/value_builder.hpp>

#include "../common/conversion_test.hpp"

template <>
struct Conversion<formats::json::Value> : public ::testing::Test {
  using ValueBuilder = formats::json::ValueBuilder;
  using Value        = formats::json::Value;
  using Exception    = formats::json::Exception;
};

INSTANTIATE_TYPED_TEST_SUITE_P(FormatsJson, Conversion, formats::json::Value);
