#pragma once

#if __clang_major__ >= 13
  #define LRW_IMPL_LIFETIME_BOUND [[clang::lifetimebound]]
#else
  #define LRW_IMPL_LIFETIME_BOUND
#endif
