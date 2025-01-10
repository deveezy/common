#include <formats/common/transfer_tag.hpp>

#include <utility>

#include <gtest/gtest.h>

#include <formats/json/serialize.hpp>
#include <formats/json/value.hpp>
#include <formats/json/value_builder.hpp>
#include <formats/yaml/serialize.hpp>
#include <formats/yaml/value.hpp>
#include <formats/yaml/value_builder.hpp>

namespace {

using ValueTypes = ::testing::Types<formats::json::Value, formats::yaml::Value>;

template <typename T>
class ValueBuilderTransfer : public ::testing::Test {};

}  // namespace

using TransferTag = formats::common::TransferTag;

TYPED_TEST_SUITE(ValueBuilderTransfer, ValueTypes);

TYPED_TEST(ValueBuilderTransfer, Basic) {
  using ValueBuilder = typename TypeParam::Builder;
  ValueBuilder root;
  root["a"]["b"] = 1;
  ValueBuilder a(TransferTag(), std::move(root["a"]));
  a["b"] = 2;
  ASSERT_EQ(root.ExtractValue()["a"]["b"].template As<int>(), 2);
}

TYPED_TEST(ValueBuilderTransfer, AssignmentAffectsPointerToSame) {
  using ValueBuilder = typename TypeParam::Builder;
  ValueBuilder root;
  root["a"] = 1;
  ValueBuilder a1(TransferTag(), std::move(root["a"]));
  ValueBuilder a2(TransferTag(), std::move(root["a"]));
  a1          = 2;
  auto result = std::move(a2);  // copy to new root
  ASSERT_EQ(result.ExtractValue().template As<int>(), 2);
  ASSERT_EQ(root.ExtractValue()["a"].template As<int>(), 2);
}
