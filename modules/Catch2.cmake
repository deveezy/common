FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2
  GIT_TAG        62fd660583d3ae7a7886930b413c3c570e89786c # release-1.10.0
)

FetchContent_MakeAvailable(Catch2)

# if(NOT Catch2)
#   # Module definition
#   set(Catch2 "${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include" PARENT_SCOPE)
# endif()
