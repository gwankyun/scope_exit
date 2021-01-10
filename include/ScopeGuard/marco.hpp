#pragma once
#ifndef MARCO_H
#define MARCO_H
#include "ScopeGuard/compiler_detection/short.hpp"
#include <boost/core/ref.hpp>
#include <boost/utility/result_of.hpp>

#ifndef UNIQUE_ID
#  if defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#    define UNIQUE_ID __COUNTER__
#  else
#    define UNIQUE_ID __LINE__
#  endif // defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#endif // !UNIQUE_ID

#ifndef UNIQUE_NAME_CAT
#  define UNIQUE_NAME_CAT(name, unique) name##unique
#endif // !UNIQUE_NAME_CAT

#ifndef UNIQUE_NAME
#  define UNIQUE_NAME(name, unique) UNIQUE_NAME_CAT(name, unique)
#endif // !SCOPE_GUARD_UNIQUE_NAME

#ifndef SCOPE_GUARD_HAS_CXX_11
#  if __cplusplus >= 201103L || defined(__cpp_rvalue_references)
#    define SCOPE_GUARD_HAS_CXX_11 1
#  else
#    define SCOPE_GUARD_HAS_CXX_11 0
#  endif // __cplusplus >= 201103L || defined(__cpp_rvalue_references)
#endif // !SCOPE_GUARD_HAS_CXX_11

#ifndef SCOPE_GUARD_HAS_CXX_17
#  if SCOPE_GUARD_HAS_CXX_11 && (__cplusplus >= 201703L || (defined(__cpp_variadic_templates) && defined(__cpp_rvalue_references) && defined(__cpp_lib_apply)))
#    define SCOPE_GUARD_HAS_CXX_17 1
#  else
#    define SCOPE_GUARD_HAS_CXX_17 0
#  endif // SCOPE_GUARD_HAS_CXX_11 && (__cplusplus >= 201703L || (defined(__cpp_variadic_templates) && defined(__cpp_rvalue_references) && defined(__cpp_lib_apply)))
#endif // !SCOPE_GUARD_HAS_CXX_17

#ifndef SCOPE_GUARD_ARG
#  if SCOPE_GUARD_HAS_CXX_11
#    define SCOPE_GUARD_ARG(T) T&&
#  else 
#    define SCOPE_GUARD_ARG(T) T
#  endif // SCOPE_GUARD_HAS_CXX_11
#endif // !SCOPE_GUARD_ARG

#if !SCOPE_GUARD_HAS_CXX_11
#  include <preprocessor.hpp>
#  include <apply.hpp>

#  ifndef SCOPE_GUARD
#    define SCOPE_GUARD(z, n, _) \
    template<typename CB BOOST_PP_COMMA_REPEAT_TYPENAME(z, n, T)> \
    explicit ScopeGuard( \
        boost::reference_wrapper< \
            typename boost::result_of<CB(BOOST_PP_REPEAT_TYPE(z, n, T))>::type \
        > result, \
        CB callback_ \
        BOOST_PP_COMMA_REPEAT_PARAMETER(z, n, T)) \
        : base(new BOOST_PP_CAT(CallBackT, n)< \
            CB BOOST_PP_COMMA_REPEAT_TYPE(z, n, T) \
            >(result, callback_ BOOST_PP_COMMA_REPEAT_ARGUMENT(z, n, T))) \
    { \
    } \
    template<typename CB BOOST_PP_COMMA_REPEAT_TYPENAME(z, n, T)> \
    explicit ScopeGuard( \
        CB callback_ \
        BOOST_PP_COMMA_REPEAT_PARAMETER(z, n, T)) \
        : base(new BOOST_PP_CAT(CallBackF, n)< \
            CB BOOST_PP_COMMA_REPEAT_TYPE(z, n, T) \
            >(callback_ BOOST_PP_COMMA_REPEAT_ARGUMENT(z, n, T))) \
    { \
    }
#  endif // !SCOPE_GUARD

#  ifndef SCOPE_GUARD_INIT
#    define SCOPE_GUARD_INIT(z, n, x) , x##n##_d(x##n##_)
#  endif // !SCOPE_GUARD_INIT

#  ifndef SCOPE_GUARD_CALL_VALUE
#    define SCOPE_GUARD_CALL_VALUE(z, n, x) BOOST_PP_COMMA_IF(n) x##n##_d
#  endif // !SCOPE_GUARD_CALL_VALUE

#  ifndef SCOPE_GUARD_VALUE
#    define SCOPE_GUARD_VALUE(z, n, x) x##n x##n##_d;
#  endif // !SCOPE_GUARD_VALUE

#  ifndef SCOPE_GUARD_CALLBACK
#    define SCOPE_GUARD_CALLBACK(z, n, _) \
    template<typename CB BOOST_PP_COMMA_REPEAT_TYPENAME(z, n, T)> /* , typename T0, typename T1 ... */ \
    struct BOOST_PP_CAT(CallBackF, n) : public Base /* CallBackF0() */ \
    { \
        BOOST_PP_CAT(CallBackF, n)( \
            CB callback_ \
            BOOST_PP_COMMA_REPEAT_PARAMETER(z, n, T)) /* , SCOPE_GUARD_ARG(T0) _T0, SCOPE_GUARD_ARG(T1) _T1 ... */ \
            : callback(callback_) \
            BOOST_PP_REPEAT_Z(z, n, SCOPE_GUARD_INIT, T) /* , T0_(_T0), T1_(_T1) ... */ \
        { \
        } \
        ~BOOST_PP_CAT(CallBackF, n)() /* ~CallBackF0() */ \
        { \
            if (!dismissed) \
            { \
                callback(BOOST_PP_REPEAT_Z(z, n, SCOPE_GUARD_CALL_VALUE, T)); /* , T0_, T1_ ... */ \
            } \
        } \
        CB callback; \
        BOOST_PP_REPEAT_Z(z, n, SCOPE_GUARD_VALUE, T) /* T0& T0_; T1& T1_; ... */ \
    }; \
    template<typename CB BOOST_PP_COMMA_REPEAT_TYPENAME(z, n, T)> /* , typename T0, typename T1 ... */ \
    struct BOOST_PP_CAT(CallBackT, n) : public Base /* CallBackT0() */ \
    { \
        BOOST_PP_CAT(CallBackT, n)( \
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT_TYPE(z, n, T))>::type> result_, \
            CB callback_ \
            BOOST_PP_COMMA_REPEAT_PARAMETER(z, n, T)) /* , SCOPE_GUARD_ARG(T0) _T0, SCOPE_GUARD_ARG(T1) _T1 ... */ \
            : callback(callback_) \
            BOOST_PP_REPEAT_Z(z, n, SCOPE_GUARD_INIT, T) /* , T0_(_T0), T1_(_T1) ... */ \
            , result(result_) \
        { \
        } \
        ~BOOST_PP_CAT(CallBackT, n)() /* ~CallBackT0() */ \
        { \
            if (!dismissed) \
            { \
                result.get() = callback(BOOST_PP_REPEAT_Z(z, n, SCOPE_GUARD_CALL_VALUE, T)); /* , T0_, T1_ ... */ \
            } \
        } \
        CB callback; \
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT_TYPE(z, n, T))>::type> result; \
        BOOST_PP_REPEAT_Z(z, n, SCOPE_GUARD_VALUE, T) /* T0 T0_; T1 T1_; ... */ \
    };
#  endif // !SCOPE_GUARD_CALLBACK
#endif // !SCOPE_GUARD_HAS_CXX_11

#endif // !MARCO_H
