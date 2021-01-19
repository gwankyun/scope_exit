#pragma once
#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <utility> // std::move std::forward
#include <functional>
#include <cassert>
#include <has_include.hpp>
#include "ScopeGuard/compiler_detection/short.hpp"
#include <boost/core/ref.hpp>
#include <boost/utility/result_of.hpp>
#include <preprocessor.hpp>

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

#if HAS_INCLUDE(tuple)
#  include <tuple> // std::tuple std::apply std::forward_as_tuple
#endif // HAS_INCLUDE(tuple)

#if HAS_INCLUDE(type_traits)
#  include <type_traits> // std::true_type std::false_type std::is_function
#endif // HAS_INCLUDE(type_traits)

//#include "ScopeGuard/marco.hpp"
#include <apply.hpp>

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
    template<typename CB, typename T0>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(T0)>::type> result,
        CB callback,
        T0 T0_)
        : base(new CallBackT1(result, callback, boost::tuple<T0>(T0_)))
    {
    }

    template<typename CB, typename T0>
    explicit ScopeGuard(
        CB callback,
        T0 T0_)
        : base(new CallBackF1(callback, boost::tuple<T0>(T0_)))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(2, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(2, BOOST_PP_PARAMETER, T))
        : base(new CallBackT2(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(2, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(2, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(2, BOOST_PP_PARAMETER, T))
        : base(new CallBackF2(
            callback,
            boost::tuple<BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(2, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(3, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(3, BOOST_PP_PARAMETER, T))
        : base(new CallBackT3(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(3, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(3, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(3, BOOST_PP_PARAMETER, T))
        : base(new CallBackF3(
            callback,
            boost::tuple<BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(3, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(4, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(4, BOOST_PP_PARAMETER, T))
        : base(new CallBackT4(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(4, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(4, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(4, BOOST_PP_PARAMETER, T))
        : base(new CallBackF4(
            callback,
            boost::tuple<BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(4, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(5, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(5, BOOST_PP_PARAMETER, T))
        : base(new CallBackT5(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(5, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(5, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(5, BOOST_PP_PARAMETER, T))
        : base(new CallBackF5(
            callback,
            boost::tuple<BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(5, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(6, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(6, BOOST_PP_PARAMETER, T))
        : base(new CallBackT6(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(6, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(6, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(6, BOOST_PP_PARAMETER, T))
        : base(new CallBackF6(
            callback,
            boost::tuple<BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(6, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(7, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(7, BOOST_PP_PARAMETER, T))
        : base(new CallBackT7(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(7, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(7, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(7, BOOST_PP_PARAMETER, T))
        : base(new CallBackF7(
            callback,
            boost::tuple<BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(7, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(8, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(8, BOOST_PP_PARAMETER, T))
        : base(new CallBackT8(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(8, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(8, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(8, BOOST_PP_PARAMETER, T))
        : base(new CallBackF8(
            callback,
            boost::tuple<BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(8, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(9, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T))>::type> result,
        CB callback,
        BOOST_PP_REPEAT(9, BOOST_PP_PARAMETER, T))
        : base(new CallBackT9(
            result,
            callback,
            boost::tuple<BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(9, BOOST_PP_ARGUMENT, T))))
    {
    }

    template<typename CB, BOOST_PP_REPEAT(9, BOOST_PP_TYPENAME, T)>
    explicit ScopeGuard(
        CB callback,
        BOOST_PP_REPEAT(9, BOOST_PP_PARAMETER, T))
        : base(new CallBackF9(
            callback,
            boost::tuple<BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T)>(BOOST_PP_REPEAT(9, BOOST_PP_ARGUMENT, T))))
    {
    }
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
    template<typename CB, typename T0>
    class CallBackT1 : public Base
    {
    public:
        CallBackT1(
            boost::reference_wrapper<typename boost::result_of<CB(T0)>::type> result,
            CB callback,
            boost::tuple<T0> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT1()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(T0)>::type> result_;
        CB callback_;
        boost::tuple<T0> tuple_;
    };

    template<typename CB, typename T0>
    class CallBackF1 : public Base
    {
    public:
        CallBackF1(
            CB callback,
            boost::tuple<T0> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF1()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<T0> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(2, BOOST_PP_TYPENAME, T)>
    class CallBackT2 : public Base
    {
    public:
        CallBackT2(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT2()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(2, BOOST_PP_TYPENAME, T)>
    class CallBackF2 : public Base
    {
    public:
        CallBackF2(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF2()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(2, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(3, BOOST_PP_TYPENAME, T)>
    class CallBackT3 : public Base
    {
    public:
        CallBackT3(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT3()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(3, BOOST_PP_TYPENAME, T)>
    class CallBackF3 : public Base
    {
    public:
        CallBackF3(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF3()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(3, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(4, BOOST_PP_TYPENAME, T)>
    class CallBackT4 : public Base
    {
    public:
        CallBackT4(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT4()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(4, BOOST_PP_TYPENAME, T)>
    class CallBackF4 : public Base
    {
    public:
        CallBackF4(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF4()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(4, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(5, BOOST_PP_TYPENAME, T)>
    class CallBackT5 : public Base
    {
    public:
        CallBackT5(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT5()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(5, BOOST_PP_TYPENAME, T)>
    class CallBackF5 : public Base
    {
    public:
        CallBackF5(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF5()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(5, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(6, BOOST_PP_TYPENAME, T)>
    class CallBackT6 : public Base
    {
    public:
        CallBackT6(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT6()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(6, BOOST_PP_TYPENAME, T)>
    class CallBackF6 : public Base
    {
    public:
        CallBackF6(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF6()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(6, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(7, BOOST_PP_TYPENAME, T)>
    class CallBackT7 : public Base
    {
    public:
        CallBackT7(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT7()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(7, BOOST_PP_TYPENAME, T)>
    class CallBackF7 : public Base
    {
    public:
        CallBackF7(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF7()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(7, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(8, BOOST_PP_TYPENAME, T)>
    class CallBackT8 : public Base
    {
    public:
        CallBackT8(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT8()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(8, BOOST_PP_TYPENAME, T)>
    class CallBackF8 : public Base
    {
    public:
        CallBackF8(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF8()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(8, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(9, BOOST_PP_TYPENAME, T)>
    class CallBackT9 : public Base
    {
    public:
        CallBackT9(
            boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T))>::type> result,
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T)> tpl)
            : result_(result)
            , callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackT9()
        {
            result_.get() = lite::apply(callback_, tuple_);
        }
        boost::reference_wrapper<typename boost::result_of<CB(BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T))>::type> result_;
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T)> tuple_;
    };

    template<typename CB, BOOST_PP_REPEAT(9, BOOST_PP_TYPENAME, T)>
    class CallBackF9 : public Base
    {
    public:
        CallBackF9(
            CB callback,
            boost::tuple<BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T)> tpl)
            : callback_(callback)
            , tuple_(tpl)
        {
        }
        ~CallBackF9()
        {
            lite::apply(callback_, tuple_);
        }
        CB callback_;
        boost::tuple<BOOST_PP_REPEAT(9, BOOST_PP_TYPE, T)> tuple_;
    };
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
