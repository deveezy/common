#pragma once

#if __cpp_consteval >= 201811L || ((__GNUC__ >= 10 || __clang_major__ >= 14) && __cplusplus >= 202002L)
  #define LRW_IMPL_CONSTEVAL consteval
#else
  #define LRW_IMPL_CONSTEVAL constexpr
#endif

#if __cpp_constinit >= 201907L
  #define LRW_IMPL_CONSTINIT constinit
#else
  #define LRW_IMPL_CONSTINIT
#endif
