#pragma once

#ifndef SCOPE_EXIT_MODULE_EXPORT
#  ifdef SCOPE_EXIT_MODULE
#    define SCOPE_EXIT_MODULE_EXPORT export
#  else
#    define SCOPE_EXIT_MODULE_EXPORT
#  endif // SCOPE_EXIT_MODULE
#endif   // !SCOPE_EXIT_MODULE_EXPORT

#ifndef SCOPE_EXIT_MODULE_INLINE
#  ifdef SCOPE_EXIT_MODULE
#    define SCOPE_EXIT_MODULE_INLINE
#  else
#    define SCOPE_EXIT_MODULE_INLINE inline
#  endif // SCOPE_EXIT_MODULE
#endif   // !SCOPE_EXIT_MODULE_INLINE

#ifndef SCOPE_EXIT_MODULE_INLINE_VALUE
#  ifdef SCOPE_EXIT_MODULE
#    define SCOPE_EXIT_MODULE_INLINE_VALUE inline
#  else
#    define SCOPE_EXIT_MODULE_INLINE_VALUE static
#  endif // SCOPE_EXIT_MODULE
#endif   // !SCOPE_EXIT_MODULE_INLINE_VALUE

#ifndef CXX_VER
#  ifdef _MSVC_LANG
#    define CXX_VER _MSVC_LANG
#  else
#    define CXX_VER __cplusplus
#  endif // _MSVC_LANG
#endif   // !CXX_VER
