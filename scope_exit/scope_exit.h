#pragma once
#include "src/unique.h"

#ifndef ON_SCOPE_EXIT
#  define ON_SCOPE_EXIT(...) \
      lite::scope_exit UNIQUE_NAME(scope_exit, UNIQUE_ID)( \
          lite::make_callback(__VA_ARGS__))
#endif
