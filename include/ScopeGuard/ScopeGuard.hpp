#pragma once
#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <utility> // std::move std::forward

#if defined(__cpp_lib_apply)
#include <tuple> // std::tuple std::apply
#endif // defined(__cpp_lib_apply)

#include "compiler_detection.h"
#include "marco.h"
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/inc.hpp>

#ifndef SCOPE_GUARD_ARG
#ifdef __cpp_rvalue_references
#define SCOPE_GUARD_ARG(T) T&&
#else 
#define SCOPE_GUARD_ARG(T) T&
#endif // __cpp_rvalue_references
#endif // !SCOPE_GUARD_ARG

#ifndef SCOPE_GUARD_HAS_CXX_17
#if defined(__cpp_variadic_templates) && defined(__cpp_rvalue_references) && defined(__cpp_lib_apply)
#define SCOPE_GUARD_HAS_CXX_17 1
#else
#define SCOPE_GUARD_HAS_CXX_17 0
#endif // defined(__cpp_variadic_templates) && defined(__cpp_rvalue_references) && defined(__cpp_lib_apply)
#endif // !SCOPE_GUARD_HAS_CXX_17

#define SCOPE_GUARD_TYPENAME(z, n, x) , typename x##n

#define SCOPE_GUARD_PARAMETER(z, n, x) , SCOPE_GUARD_ARG(x##n) _##x##n

#define SCOPE_GUARD_ARGUMENT(z, n, x) , _##x##n

#define SCOPE_GUARD_TYPE(z, n, x) , x##n

#ifndef BOOST_PP_REPEAT_Z
#define BOOST_PP_REPEAT_Z(z) BOOST_PP_REPEAT_##z
#endif // !BOOST_PP_REPEAT_Z

#define SCOPE_GUARD(z, n, _) \
    template<typename CB BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_TYPENAME, T)> /* , typename T0, typename T1 ... */ \
    explicit ScopeGuard(CB callback_ \
        BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_PARAMETER, T)) /* , SCOPE_GUARD_ARG(T0) _T0, SCOPE_GUARD_ARG(T1) _T1 ... */ \
        : dismissed(false) \
        , base(new BOOST_PP_CAT(CallBack, n)<CB BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_TYPE, T)> /* , T0, T1 ... */ \
            (callback_ BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_ARGUMENT, T))) /* , _T0, _T1 ... */ \
    { \
    }

#define SCOPE_GUARD_INIT(z, n, x) , x##n##_(_##x##n##)
#define SCOPE_GUARD_CALL_VALUE(z, n, x) BOOST_PP_COMMA_IF(n) x##n##_
#define SCOPE_GUARD_VALUE(z, n, x) x##n& x##n##_;

#define SCOPE_GUARD_CALLBACK(z, n, _) \
    template<typename CB BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_TYPENAME, T)> /* , typename T0, typename T1 ... */ \
    struct BOOST_PP_CAT(CallBack, n) : public Base \
    { \
        BOOST_PP_CAT(CallBack, n)(CB callback_ BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_PARAMETER, T)) /* , SCOPE_GUARD_ARG(T0) _T0, SCOPE_GUARD_ARG(T1) _T1 ... */ \
            : callback(callback_) BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_INIT, T) /* , T0_(_T0), T1_(_T1) ... */ \
        { \
        } \
        ~BOOST_PP_CAT(CallBack, n)() \
        { \
            callback(BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_CALL_VALUE, T)); /* , T0_, T1_ ... */ \
        } \
        CB callback; \
        BOOST_PP_REPEAT_Z(z)(n, SCOPE_GUARD_VALUE, T) /* T0& T0_; T1& T1_; ... */ \
    };

class ScopeGuard
{
public:

#if FEATURE_COMPILER_CXX_STRONG_ENUMS
    enum struct Type { Delete = 0, DeleteArray };
    static const Type Delete = Type::Delete;
    static const Type DeleteArray = Type::DeleteArray;
#else
    enum Type { Delete = 0, DeleteArray };
#endif // FEATURE_COMPILER_CXX_STRONG_ENUMS

#if SCOPE_GUARD_HAS_CXX_17
    template<typename CB, typename ...Args>
    explicit ScopeGuard(CB callback_, Args&& ...args_)
        : dismissed(false)
        , base(new CallBack<CB, Args...>(callback_, std::tuple<Args&...>(std::forward<Args&>(args_)...)))
    {
    }
#else
    BOOST_PP_REPEAT(10, SCOPE_GUARD, _)
#endif // SCOPE_GUARD_HAS_CXX_17

    template<typename T>
    explicit ScopeGuard(Type type, T*& value_)
        : dismissed(false), base(new Ptr<T>(type, value_))
    {
    }

    ~ScopeGuard()
    {
        if (!dismissed)
        {
            if (base != NULL)
            {
                delete base;
                base = NULL;
            }
        }
    }

    void release() FEATURE_NOEXCEPT
    {
        dismissed = true;
    }

private:

    ScopeGuard(const ScopeGuard&) FEATURE_DELETED_FUNCTION;
    ScopeGuard& operator=(const ScopeGuard&) FEATURE_DELETED_FUNCTION;

    struct Base
    {
        Base() {}
        virtual ~Base() {}
    };

#if SCOPE_GUARD_HAS_CXX_17
    template<typename CB, typename ...Args>
    struct CallBack : public Base
    {
        CallBack(CB callback_, SCOPE_GUARD_ARG(std::tuple<Args&...>) args_)
            : callback(callback_), args(args_)
        {
        }

        ~CallBack()
        {
            std::apply(callback, args);
        }

        CB callback;
        std::tuple<Args&...> args;
    };
#else
    BOOST_PP_REPEAT(10, SCOPE_GUARD_CALLBACK, _)
#endif // SCOPE_GUARD_HAS_CXX_17

    template<typename T>
    struct Ptr : public Base
    {
        Ptr(Type type_, T*& value_) : type(type_), value(value_)
        {
        }

        ~Ptr()
        {
            if (value != NULL)
            {
                switch (type)
                {
                case ScopeGuard::Delete:
                    delete value;
                    value = NULL;
                    break;
                case ScopeGuard::DeleteArray:
                    delete[] value;
                    value = NULL;
                    break;
                default:
                    break;
                }
            }
        }

        T*& value;
        Type type;
    };

    bool dismissed;
    Base* base;
};

#ifndef ON_SCOPE_EXIT
#define ON_SCOPE_EXIT(...) ScopeGuard UNIQUE_NAME(ScopeGuard_, UNIQUE)(##__VA_ARGS__)
#endif // !ON_SCOPE_EXIT

#endif // !SCOPE_GUARD_HPP
