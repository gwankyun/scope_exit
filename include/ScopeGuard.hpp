#pragma once
#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <utility> // std::move std::forward
#include <functional>
#include <cassert>
#include <has_include.hpp>

#if HAS_INCLUDE(tuple)
#  include <tuple> // std::tuple std::apply std::forward_as_tuple
#endif // HAS_INCLUDE(tuple)

#if HAS_INCLUDE(type_traits)
#  include <type_traits> // std::true_type std::false_type std::is_function
#endif // HAS_INCLUDE(type_traits)

#include "ScopeGuard/marco.hpp"

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

#if SCOPE_GUARD_HAS_CXX_11
    template<typename R,
        typename CB,
        typename ...Args>
    explicit ScopeGuard(
        std::reference_wrapper<R> result,
        CB callback,
        Args&&... args)
        : base(onDestroy([result, callback, &args...]()
            {
                result.get() = callback(std::forward<Args>(args)...);
            }))
    {
    }

    template<typename CB, typename ...Args>
    explicit ScopeGuard(
        CB callback,
        Args&&... args)
        : base(onDestroy([callback, &args...]()
            {
                callback(std::forward<Args>(args)...);
            }))
    {
    }

#else
    //template<typename CB>
    //explicit ScopeGuard(
    //    boost::reference_wrapper<typename boost::result_of<CB()>::type> result,
    //    CB callback_)
    //{
    //}
    BOOST_PP_REPEAT(10, SCOPE_GUARD, _)
#endif // SCOPE_GUARD_HAS_CXX_11

    template<typename T>
    explicit ScopeGuard(Type type, T*& value_)
        : base(new Ptr<T>(type, value_))
    {
    }

    ~ScopeGuard()
    {
        reset();
    }

    void release() NOEXCEPT
    {
        base->dismissed = true;
    }

    void reset() NOEXCEPT
    {
        if (base != NULLPTR)
        {
            delete base;
            base = NULLPTR;
        }
    }

private:

    ScopeGuard(const ScopeGuard&) DELETED_FUNCTION;
    ScopeGuard& operator=(const ScopeGuard&) DELETED_FUNCTION;

    struct Base
    {
        Base(): dismissed(false) {}
        virtual ~Base() {}
        bool dismissed;
    };

#if SCOPE_GUARD_HAS_CXX_11
    template<typename Fn>
    struct CallBack : public Base
    {
        CallBack(Fn fn_)
            : fn(fn_)
        {
        }

        ~CallBack()
        {
            if (!dismissed)
            {
                fn();
            }
        }

        Fn fn;
    };

    template<typename Fn>
    inline Base* onDestroy(Fn fn)
    {
        return new CallBack<Fn>(fn);
    };

#else
    BOOST_PP_REPEAT(10, SCOPE_GUARD_CALLBACK, _)
#endif // SCOPE_GUARD_HAS_CXX_11

    template<typename T>
    struct Ptr : public Base
    {
        Ptr(const Type& type_, T*& value_)
            : type(type_)
            , value(value_)
        {
        }

        ~Ptr()
        {
            if (!dismissed && value != NULLPTR)
            {
                switch (type)
                {
                case ScopeGuard::Delete:
                    delete value;
                    value = NULLPTR;
                    break;
                case ScopeGuard::DeleteArray:
                    delete[] value;
                    value = NULLPTR;
                    break;
                default:
                    assert(false);
                    break;
                }
            }
        }

        T*& value;
        Type type;
    };

    Base* base;
};

#if SCOPE_GUARD_HAS_CXX_11
#  define SCOPE_GUARD_REF(x) std::ref(x)
#  define SCOPE_GUARD_CREF(x) std::cref(x)
#else 
#  define SCOPE_GUARD_REF(x) boost::ref(x)
#  define SCOPE_GUARD_CREF(x) boost::cref(x)
#endif // SCOPE_GUARD_HAS_CXX_11

#ifndef ON_SCOPE_EXIT
#  define ON_SCOPE_EXIT(...) ScopeGuard UNIQUE_NAME(ScopeGuard_, UNIQUE_ID)(##__VA_ARGS__)
#endif // !ON_SCOPE_EXIT

#endif // !SCOPE_GUARD_HPP
