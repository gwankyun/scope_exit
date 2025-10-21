#pragma once
#include "src/unique.h"

#ifndef LOCAL_FUNCTION_BEGIN
#  define LOCAL_FUNCTION_BEGIN(_ret) \
      struct UNIQUE_NAME(LocalFunction_, UNIQUE_ID) \
      { \
          _ret operator()
#endif // !LOCAL_FUNCTION_BEGIN

#ifndef LOCAL_FUNCTION_END
#  define LOCAL_FUNCTION_END(_name) \
      } \
      _name
#endif // !LOCAL_FUNCTION_END
