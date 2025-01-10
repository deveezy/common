#include <gtest/gtest.h>

#include "../common/roundtrip_test.hpp"
#include <formats/yaml/value_builder.hpp>

INSTANTIATE_TYPED_TEST_SUITE_P(FormatsYaml, Roundtrip, formats::yaml::ValueBuilder);
