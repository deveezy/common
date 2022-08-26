cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(cppcommon)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(compiler_features)
include(compiler_warnings)
include(platform_features)
include(system_information)

find_package(Threads REQUIRED)

if(UNIX AND NOT APPLE AND NOT MSYS)
  # find_package(LibBFD)
  # find_package(LibDL)
  # find_package(LibRT)
  # find_package(LibUUID)
endif()

if(WIN32 OR MSYS)
  find_package(DbgHelp)
  find_package(RPC)
  find_package(Userenv)
endif()

add_subdirectory("modules")

# Link libraries
list(APPEND LINKLIBS Threads::Threads)

if(UNIX AND NOT APPLE AND NOT MSYS)
  list(APPEND LINKLIBS ${LIBBFD_LIBRARIES})
  list(APPEND LINKLIBS ${LIBDL_LIBRARIES})
  list(APPEND LINKLIBS ${LIBRT_LIBRARIES})
  list(APPEND LINKLIBS ${LIBUUID_LIBRARIES})
endif()

if(WIN32 OR MSYS)
  list(APPEND LINKLIBS ${DBGHELP_LIBRARIES})
  list(APPEND LINKLIBS ${RPC_LIBRARIES})
  list(APPEND LINKLIBS ${USERENV_LIBRARIES})
  list(APPEND LINKLIBS ${VLD_LIBRARIES})
endif()

# System directories
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/modules")
include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/plugins")

# Library
set(LIB_HEADER_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/include/system/console.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/system/environment.hpp"
)
set(LIB_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/source/system/console.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/system/environment.cpp"
)
add_library(${CMAKE_PROJECT_NAME} ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "libraries")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" PUBLIC ${vld})

# external libs
target_link_libraries(${CMAKE_PROJECT_NAME} ${LINKLIBS} fmt)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
target_link_libraries(${CMAKE_PROJECT_NAME} Catch2::Catch2)

list(APPEND INSTALL_TARGETS ${CMAKE_PROJECT_NAME})
list(APPEND LINKLIBS ${CMAKE_PROJECT_NAME})

if(NOT CPPCOMMON_MODULE)
  # # Examples
  file(GLOB EXAMPLE_HEADER_FILES "examples/*.hpp")
  file(GLOB EXAMPLE_INLINE_FILES "examples/*.inl")
  file(GLOB EXAMPLE_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/examples" "examples/*.cpp")

  foreach(EXAMPLE_SOURCE_FILE ${EXAMPLE_SOURCE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" EXAMPLE_NAME ${EXAMPLE_SOURCE_FILE})
    set(EXAMPLE_TARGET "cppcommon-example-${EXAMPLE_NAME}")
    add_executable(${EXAMPLE_TARGET} ${EXAMPLE_HEADER_FILES} ${EXAMPLE_INLINE_FILES} "examples/${EXAMPLE_SOURCE_FILE}")
    target_include_directories(${EXAMPLE_TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    add_dependencies(${EXAMPLE_TARGET} ${CMAKE_PROJECT_NAME})
    set_target_properties(${EXAMPLE_TARGET} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "examples")
    target_link_libraries(${EXAMPLE_TARGET} ${LINKLIBS})

    # list(APPEND INSTALL_TARGETS ${EXAMPLE_TARGET})
    # list(APPEND INSTALL_TARGETS_PDB ${EXAMPLE_TARGET})
  endforeach()
endif()
