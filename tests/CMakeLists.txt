if(NOT TARGET gtest)
  if(NOT EXISTS "${CMAKE_SOURCE_DIR}/external/googletest")
    message(
      FATAL_ERROR
        "googletest submodule is missing. Please run 'git submodule update --init'."
    )
  else()
    add_subdirectory("${CMAKE_SOURCE_DIR}/external/googletest"
                     ${CMAKE_BINARY_DIR}/external/googletest)
  endif()

endif()

enable_testing()

add_executable(
  tests
  string_to_duration_test.cpp
  trivial_map_test.cpp
  not_null_test.cpp
  shared_readable_ptr_test.cpp
  meta_test.cpp
  underlying_value_test.cpp
  strong_typedef_test.cpp
  ip_test.cpp
  macaddr_test.cpp
  datetime_test.cpp
  c_file_test.cpp
  file_descriptor_test.cpp
  # formats common
  formats/common/conversion_test.hpp
  formats/common/items_test.cpp
  formats/common/member_access_test.hpp
  formats/common/member_modify_test.hpp
  formats/common/merge_test.hpp
  formats/common/roundtrip_test.hpp
  formats/common/serialize_test.hpp
  formats/common/transfer_tag_test.cpp
  formats/common/utils_test.hpp
  formats/common/utils_test.cpp
  formats/common/value_builder_test.cpp
  formats/common/value_builder_test.hpp
  formats/common/value_test.hpp
  formats/common/value_test.cpp
  # formats json
  formats/json/boost_uuid_test.cpp
  formats/json/boost_uuid_test.cpp
  formats/json/member_access_test.cpp
  formats/json/member_modify_test.cpp
  formats/json/merge_test.cpp
  formats/json/parse_test.cpp
  formats/json/rapidjson_contiguous_test.cpp
  formats/json/roundtrip_test.cpp
  formats/json/schema_test.cpp
  formats/json/serialize_test.cpp
  formats/json/string_builder_test.cpp
  formats/json/value_builder_test.cpp
  formats/json/value_test.cpp
  formats/json/parser/parser_test.cpp
  # formats yaml
  formats/yaml/member_access_test.cpp
  formats/yaml/member_modify_test.cpp
  formats/yaml/merge_test.cpp
  formats/yaml/roundtrip_test.cpp
  formats/yaml/serialize_test.cpp
  formats/yaml/utils_test.cpp
  formats/yaml/value_builder_test.cpp
  formats/yaml/value_location_test.cpp
  formats/yaml/value_test.cpp
  main.cpp)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
target_include_directories(
  tests PRIVATE ${INCLUDE_DIR} ${SRC_DIR}
                ${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)
target_link_libraries(tests gtest gtest_main gmock common)
