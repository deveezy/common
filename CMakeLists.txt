cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

set(CMAKE_CXX_STANDARD 23)
set(LRW_CMAKE_DIR ${CMAKE_SOURCE_DIR}/cmake)

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}")

include(${LRW_CMAKE_DIR}/SetupLTO.cmake)

project(demo)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

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

  ${INCLUDE_DIR}/formats/common/meta.hpp
  ${INCLUDE_DIR}/formats/parse/common.hpp
  ${INCLUDE_DIR}/formats/parse/to.hpp
  ${INCLUDE_DIR}/formats/parse/variant.hpp

  ${SRC_DIR}/compiler/demangle.cpp

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
  ${SRC_DIR}/utils/uuid4.cpp
  ${SRC_DIR}/utils/boost_uuid4.cpp

  ${SRC_DIR}/fs/c_file.cpp
  ${SRC_DIR}/fs/file_descriptor.cpp
  ${SRC_DIR}/fs/temp_file.cpp
  ${SRC_DIR}/fs/temp_directory.cpp
  ${SRC_DIR}/fs/read.cpp
  ${SRC_DIR}/fs/write.cpp
)

target_include_directories(${LIB_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${LIB_NAME} PRIVATE fmt cctz)

add_executable(exe ${CMAKE_SOURCE_DIR}/exe/time_of_day_exe.cpp)
target_link_libraries(exe PRIVATE ${LIB_NAME})
target_include_directories(exe PRIVATE ${INCLUDE_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

include(${LRW_CMAKE_DIR}/SetupLTO.cmake)

# add_executable(${CMAKE_PROJECT_NAME}
#   # "src/main.cpp"
#   "src/RuwarePropDemo.cpp"
#   # "src/leveldb_try.cpp"
#   # "src/json_wrapper/demo.cpp"
#   )

# target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Werror -Wno-unused-function -Wno-unused-variable)

