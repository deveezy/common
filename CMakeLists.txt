cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

set(CMAKE_CXX_STANDARD 23)
set(LRW_CMAKE_DIR ${CMAKE_SOURCE_DIR}/cmake)

project(demo)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# just for fun
set(BUILD_LIB ON)

set(LIB_NAME common)

add_library(
  ${LIB_NAME}
  ${INCLUDE_DIR}/fs/c_file.hpp
  ${INCLUDE_DIR}/fs/file_descriptor.hpp
  ${INCLUDE_DIR}/fs/open_mode.hpp
  ${INCLUDE_DIR}/fs/read.hpp
  ${INCLUDE_DIR}/fs/write.hpp
  ${INCLUDE_DIR}/fs/temp_file.hpp
  ${INCLUDE_DIR}/fs/temp_directory.hpp
  ${INCLUDE_DIR}/utils/datetime.hpp
  ${INCLUDE_DIR}/utils/fast_pimpl.hpp
  ${INCLUDE_DIR}/utils/flags.hpp
  ${INCLUDE_DIR}/utils/meta.hpp
  ${INCLUDE_DIR}/utils/meta_light.hpp
  ${INCLUDE_DIR}/utils/string_to_duration.hpp
  ${INCLUDE_DIR}/utils/void_t.hpp
  ${INCLUDE_DIR}/utils/uuid4.hpp
  ${INCLUDE_DIR}/compiler/thread_local.hpp
  ${INCLUDE_DIR}/formats/common/meta.hpp
  ${INCLUDE_DIR}/formats/common/conversion_stack.hpp
  ${INCLUDE_DIR}/formats/common/items.hpp
  ${INCLUDE_DIR}/formats/common/iterator_direction.hpp
  ${INCLUDE_DIR}/formats/common/merge.hpp
  ${INCLUDE_DIR}/formats/common/meta.hpp
  ${INCLUDE_DIR}/formats/common/path.hpp
  ${INCLUDE_DIR}/formats/common/transfer_tag.hpp
  ${INCLUDE_DIR}/formats/common/type.hpp
  ${INCLUDE_DIR}/formats/common/utils.hpp
  ${INCLUDE_DIR}/formats/common/validations.hpp
  ${INCLUDE_DIR}/formats/parse/common.hpp
  ${INCLUDE_DIR}/formats/parse/common_containers.hpp
  ${INCLUDE_DIR}/formats/parse/to.hpp
  ${INCLUDE_DIR}/formats/parse/variant.hpp
  ${INCLUDE_DIR}/formats/parse/optional.hpp
  ${INCLUDE_DIR}/formats/serialize/common_containers.hpp
  ${INCLUDE_DIR}/formats/serialize/time_of_day.hpp
  ${INCLUDE_DIR}/formats/serialize/to.hpp
  ${INCLUDE_DIR}/formats/serialize/variant.hpp
  ${INCLUDE_DIR}/formats/serialize/write_to_stream.hpp
  ${INCLUDE_DIR}/formats/json/impl/mutable_value_wrapper.hpp
  ${INCLUDE_DIR}/formats/json/impl/types.hpp
  ${INCLUDE_DIR}/formats/json/parser/array_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/base_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/bool_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/exception.hpp
  ${INCLUDE_DIR}/formats/json/parser/int_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/map_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/number_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/parser_handler.hpp
  ${INCLUDE_DIR}/formats/json/parser/parser_json.hpp
  ${INCLUDE_DIR}/formats/json/parser/parser_state.hpp
  ${INCLUDE_DIR}/formats/json/parser/string_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/typed_parser.hpp
  ${INCLUDE_DIR}/formats/json/parser/validator.hpp
  ${INCLUDE_DIR}/formats/json/exception.hpp
  ${INCLUDE_DIR}/formats/json/inline.hpp
  ${INCLUDE_DIR}/formats/json/iterator.hpp
  ${INCLUDE_DIR}/formats/json/schema.hpp
  ${INCLUDE_DIR}/formats/json/serialize.hpp
  ${INCLUDE_DIR}/formats/json/serialize_container.hpp
  ${INCLUDE_DIR}/formats/json/serialize_duration.hpp
  ${INCLUDE_DIR}/formats/json/serialize_variant.hpp
  ${INCLUDE_DIR}/formats/json/string_builder.hpp
  ${INCLUDE_DIR}/formats/json/string_builder_fwd.hpp
  ${INCLUDE_DIR}/formats/json/value.hpp
  ${INCLUDE_DIR}/formats/json/value_builder.hpp
  ${INCLUDE_DIR}/formats/json.hpp
  ${INCLUDE_DIR}/formats/json_fwd.hpp
  ${INCLUDE_DIR}/formats/yaml.hpp
  ${INCLUDE_DIR}/formats/yaml_fwd.hpp
  ${INCLUDE_DIR}/formats/yaml/exception.hpp
  ${INCLUDE_DIR}/formats/yaml/iterator.hpp
  ${INCLUDE_DIR}/formats/yaml/serialize.hpp
  ${INCLUDE_DIR}/formats/yaml/serialize_container.hpp
  ${INCLUDE_DIR}/formats/yaml/types.hpp
  ${INCLUDE_DIR}/formats/yaml/value.hpp
  ${INCLUDE_DIR}/formats/yaml/value_builder.hpp
  ${INCLUDE_DIR}/formats/yaml/value_fwd.hpp
  ${SRC_DIR}/formats/yaml/exception.cpp
  ${SRC_DIR}/formats/yaml/iterator.cpp
  ${SRC_DIR}/formats/yaml/serialize.cpp
  ${SRC_DIR}/formats/yaml/value.cpp
  ${SRC_DIR}/formats/yaml/value_builder.cpp
  ${SRC_DIR}/formats/yaml/exttypes.cpp
  ${SRC_DIR}/formats/yaml/exttypes.hpp
  ${SRC_DIR}/formats/common/path.cpp
  ${SRC_DIR}/formats/common/utils.cpp
  ${SRC_DIR}/formats/json/exception.cpp
  ${SRC_DIR}/formats/json/inline.cpp
  ${SRC_DIR}/formats/json/iterator.cpp
  ${SRC_DIR}/formats/json/schema.cpp
  ${SRC_DIR}/formats/json/serialize.cpp
  ${SRC_DIR}/formats/json/string_builder.cpp
  ${SRC_DIR}/formats/json/value.cpp
  ${SRC_DIR}/formats/json/value_builder.cpp
  ${SRC_DIR}/formats/json/impl/accept.cpp
  ${SRC_DIR}/formats/json/impl/mutable_value_wrapper.cpp
  ${SRC_DIR}/formats/json/impl/accept.hpp
  ${SRC_DIR}/formats/json/impl/are_equal.hpp
  ${SRC_DIR}/formats/json/impl/are_equal.cpp
  ${SRC_DIR}/formats/json/impl/exttypes.cpp
  ${SRC_DIR}/formats/json/impl/exttypes.hpp
  ${SRC_DIR}/formats/json/impl/json_tree.hpp
  ${SRC_DIR}/formats/json/impl/json_tree.cpp
  ${SRC_DIR}/formats/json/impl/types.cpp
  ${SRC_DIR}/formats/json/impl/types_impl.hpp
  ${SRC_DIR}/formats/json/parser/bool_parser.cpp
  ${SRC_DIR}/formats/json/parser/int_parser.cpp
  ${SRC_DIR}/formats/json/parser/parser_handler.cpp
  ${SRC_DIR}/formats/json/parser/parser_json.cpp
  ${SRC_DIR}/formats/json/parser/parser_state.cpp
  ${SRC_DIR}/formats/json/parser/string_parser.cpp
  ${SRC_DIR}/compiler/demangle.cpp
  ${SRC_DIR}/compiler/thread_local.cpp
  ${SRC_DIR}/utils/assert.cpp
  ${SRC_DIR}/utils/string_to_duration.cpp
  ${SRC_DIR}/utils/from_string.cpp
  ${SRC_DIR}/utils/string_to_duration.cpp
  ${SRC_DIR}/utils/datetime.cpp
  ${SRC_DIR}/utils/datetime/from_string_saturating.cpp
  ${SRC_DIR}/utils/mock_now.cpp
  ${SRC_DIR}/utils/ip.cpp
  ${SRC_DIR}/utils/macaddr.cpp
  ${SRC_DIR}/utils/encoding/hex.cpp
  ${SRC_DIR}/utils/boost_uuid4.cpp
  ${SRC_DIR}/utils/uuid4.cpp
  ${SRC_DIR}/utils/rand.cpp
  ${SRC_DIR}/fs/c_file.cpp
  ${SRC_DIR}/fs/file_descriptor.cpp
  ${SRC_DIR}/fs/temp_file.cpp
  ${SRC_DIR}/fs/temp_directory.cpp
  ${SRC_DIR}/fs/read.cpp
  ${SRC_DIR}/fs/write.cpp)

target_include_directories(
  ${LIB_NAME} PRIVATE ${INCLUDE_DIR}
                      ${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)
target_link_libraries(${LIB_NAME} PRIVATE fmt cctz yaml-cpp)

add_executable(exe ${CMAKE_SOURCE_DIR}/exe/time_of_day_exe.cpp)
if(BUILD_LIB)
  target_link_libraries(exe PRIVATE ${LIB_NAME})
  target_include_directories(exe PRIVATE ${INCLUDE_DIR})

  add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()

include(${LRW_CMAKE_DIR}/SetupLTO.cmake)
include(${LRW_CMAKE_DIR}/Sanitizers.cmake)

# sanitize_target(exe)

# target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Werror
# -Wno-unused-function -Wno-unused-variable)
