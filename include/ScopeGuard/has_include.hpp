#pragma once
#ifndef HAS_INCLUDE_HPP
#define HAS_INCLUDE_HPP

#if defined(__cplusplus) && defined(__has_include)
#  if __has_include(<version>)
#    include <version>
#  else
#    include <cstddef>
#  endif
#elif defined(__cplusplus)
#  include <cstddef>
#else
#  include <stddef.h>
#endif

#if (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
#  include "has_include/boost/config/stdlib/dinkumware.hpp"
#elif defined(_LIBCPP_VERSION)
#  include "has_include/boost/config/stdlib/libcpp.hpp"
#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
#  include "has_include/boost/config/stdlib/libstdcpp3.hpp"
#endif //  (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)

#ifndef __HAS_INCLUDE
#  if defined(__has_include)
#    define __HAS_INCLUDE(header) __has_include(<header>)
#  else
#    define __HAS_INCLUDE_cstdint !defined(BOOST_HAS_STDINT_H)
// C++11
#    define __HAS_INCLUDE_atomic !defined(BOOST_NO_CXX11_HDR_ATOMIC)
#    define __HAS_INCLUDE_array !defined(BOOST_NO_CXX11_HDR_ARRAY)
#    define __HAS_INCLUDE_chrono !defined(BOOST_NO_CXX11_HDR_CHRONO)
#    define __HAS_INCLUDE_codecvt !defined(BOOST_NO_CXX11_HDR_CODECVT)
#    define __HAS_INCLUDE_condition_variable !defined(BOOST_NO_CXX11_HDR_CONDITION_VARIABLE)
#    define __HAS_INCLUDE_exception !defined(BOOST_NO_CXX11_HDR_EXCEPTION)
#    define __HAS_INCLUDE_forward_list !defined(BOOST_NO_CXX11_HDR_FORWARD_LIST)
#    define __HAS_INCLUDE_functional !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)
#    define __HAS_INCLUDE_future !defined(BOOST_NO_CXX11_HDR_FUTURE)
#    define __HAS_INCLUDE_initializer_list !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#    define __HAS_INCLUDE_mutex !defined(BOOST_NO_CXX11_HDR_MUTEX)
#    define __HAS_INCLUDE_random !defined(BOOST_NO_CXX11_HDR_RANDOM)
#    define __HAS_INCLUDE_ratio !defined(BOOST_NO_CXX11_HDR_RATIO)
#    define __HAS_INCLUDE_regex !defined(BOOST_NO_CXX11_HDR_REGEX)
#    define __HAS_INCLUDE_system_error !defined(BOOST_NO_CXX11_HDR_SYSTEM_ERROR)
#    define __HAS_INCLUDE_thread !defined(BOOST_NO_CXX11_HDR_THREAD)
#    define __HAS_INCLUDE_tuple !defined(BOOST_NO_CXX11_HDR_TUPLE)
#    define __HAS_INCLUDE_typeindex !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)
#    define __HAS_INCLUDE_type_traits !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#    define __HAS_INCLUDE_unordered_map !defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP)
#    define __HAS_INCLUDE_unordered_set !defined(BOOST_NO_CXX11_HDR_UNORDERED_SET)
#    define __HAS_INCLUDE(header) __HAS_INCLUDE_##header
#  endif // defined(__has_include)
#endif // !__HAS_INCLUDE

#endif // !HAS_INCLUDE_HPP
