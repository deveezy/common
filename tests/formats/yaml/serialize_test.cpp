#include <gtest/gtest.h>

#include <formats/yaml/exception.hpp>
#include <formats/yaml/serialize.hpp>

#include "../common/serialize_test.hpp"

template <>
struct Serialization<formats::yaml::Value> : public ::testing::Test {
  constexpr static const char *kDoc = "key1: 1\nkey2: val";

  using ValueBuilder = formats::yaml::ValueBuilder;
  using Value        = formats::yaml::Value;
  using Type         = formats::yaml::Type;

  using ParseException         = formats::yaml::ParseException;
  using TypeMismatchException  = formats::yaml::TypeMismatchException;
  using OutOfBoundsException   = formats::yaml::OutOfBoundsException;
  using MemberMissingException = formats::yaml::MemberMissingException;
  using BadStreamException     = formats::yaml::BadStreamException;

  constexpr static auto FromString = formats::yaml::FromString;
  constexpr static auto FromStream = formats::yaml::FromStream;
};

INSTANTIATE_TYPED_TEST_SUITE_P(FormatsYaml, Serialization, formats::yaml::Value);
