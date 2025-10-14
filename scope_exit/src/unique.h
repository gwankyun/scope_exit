#pragma once

#ifndef UNIQUE_ID
#  if defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#    define UNIQUE_ID __COUNTER__
#  else
#    define UNIQUE_ID __LINE__
#  endif
#endif

#ifndef UNIQUE_NAME_CAT
#  define UNIQUE_NAME_CAT(name, unique) name##unique
#endif

#ifndef UNIQUE_NAME
#  define UNIQUE_NAME(name, unique) UNIQUE_NAME_CAT(name, unique)
#endif
